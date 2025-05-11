#include "editor/editor.h"
#include "editor.h"
#include "yr/extcore_config.h"
#include "runtime/logger/logger.h"
#include "input/input.h"
#include "core/reflection/reflection.h"
#include <map>
#include <ranges>

class YrEditor final : public YrImGuiWindow
{

    virtual void OnOpen() override;
    virtual void OnClose() override;
    virtual void OnFrame() override;

public:
    YrEditor();
    virtual ~YrEditor();
    
    std::vector<std::unique_ptr<YrEditorWindow>> windows;
};

static std::shared_ptr<YrEditor> gYrEditor;

class YrEditorWindow_Impl
{
public:
    YrEditorWindow_Impl(YrEditorWindow* window) : window(window)
    {
        if (!gYrEditor || !gYrEditor->IsOpened()) {
            YrImGui::SwitchWindow(gYrEditor);
        }
        gYrEditor->windows.push_back(std::unique_ptr<YrEditorWindow>(window));
    }
    ~YrEditorWindow_Impl()
    {
        Close();
        if (auto iter = std::find_if(gYrEditor->windows.begin(), gYrEditor->windows.end(), [=](auto& ptr) { return ptr.get() == window; }); iter != gYrEditor->windows.end())
        {
            gYrEditor->windows.erase(iter);
        }
        if (gYrEditor->windows.size() == 0 && gYrEditor->IsOpened()) {
            YrImGui::SwitchWindow(gYrEditor, true);
        }
    }

    void NewFrame()
    {
        if (_opened)
        {
            window->OnFrame();
        }
    }

    void Open()
    {
        if (_opened)
            return;

        _opened = true;
        window->OnOpen();
    }
    void Close()
    {
        if (!_opened)
            return;

        _opened = false;
        window->OnClose();
    }

    YrEditorWindow* window;
    bool _opened {false};
    bool _editorOpened {false};
};

YrEditor::YrEditor()
{

}

YrEditor::~YrEditor()
{

}

void YrEditor::OnOpen()
{
    for (auto& win : windows)
    {
        if (win->_impl->_editorOpened) {
            win->Open();
        }
    }
}

void YrEditor::OnClose()
{
    for (auto& win : windows)
    {
        win->_impl->_editorOpened = win->IsOpened();
        win->Close();
    }
}

void YrEditor::OnFrame()
{
    for (auto& win : windows)
    {
        if (win->IsOpened()) {
            win->NewFrame();
        }
    }
}


YrEditorWindow::YrEditorWindow()
{
    _impl = std::make_unique<YrEditorWindow_Impl>(this);
}

YrEditorWindow::~YrEditorWindow()
{
    _impl.reset();
}

void YrEditorWindow::NewFrame()
{
    _impl->NewFrame();
}

void YrEditorWindow::Open()
{
    _impl->Open();
}

void YrEditorWindow::Close()
{
    _impl->Close();
}

bool YrEditorWindow::IsOpened() const
{
    return _impl->_opened;
}

auto& GetKeyListeners()
{
    static std::map<gainput::Key, std::vector<YrEditorKeyListener::ListenerFuncType>> gKeyListeners {};
    return gKeyListeners;
}

gainput::Key GetConfigKey(std::string_view config)
{
    if (!gYrExtConfig)
        return gainput::KeyCount_;
    std::string str = gYrExtConfig->rawData["editor_key_config"].value(config, "KeyCount_");
    gainput::Key key = gainput::KeyCount_;
    if (Reflection::TryGetEnumValue(str, key)) {
        return key;
    }
    return key;
}

static std::vector<std::pair<std::string, YrEditorKeyListener::ListenerFuncType>> gRegisterQueue;

void YrEditorKeyListener::Register(std::string_view config, ListenerFuncType listener)
{
    gRegisterQueue.emplace_back(std::pair{config, listener});
}

void YrEditorKeyListener::Unregister(std::string_view config, ListenerFuncType listener)
{
    gainput::Key key = GetConfigKey(config);
    if (key == gainput::KeyCount_)
        return;
    auto& list = GetKeyListeners()[key];
    if (auto iter = std::find(list.begin(), list.end(), listener); iter != list.end()){
        list.erase(iter);
    }
    gLogger->info("editor: key unregister {} <- {}", config, (void*)listener);
}

void StepEditorKeyListener()
{
    if (!ImGui::GetCurrentContext())
        return;
    for (auto&& [config, listener] : gRegisterQueue)
    {
        gainput::Key key = GetConfigKey(config);
        if (key == gainput::KeyCount_)
            return;
        GetKeyListeners()[key].push_back(listener);
        gLogger->info("editor: key register {} <- {}", config, (void*)listener);
    }
    gRegisterQueue.clear();
    for (auto&& [key, list] : GetKeyListeners())
    {
        if (!Input::IsKeyDown(key))
            continue;
        for (auto const& listener : list | std::views::reverse) {
            if (listener())
                break;
        }
    }
}

#include "yr/event/ui_event.h"
#include "yr/event/general_event.h"
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent, StepEditorKeyListener)
REGISTER_YR_HOOK_EVENT_LISTENER(YrUIUpdateEvent, StepEditorKeyListener)
