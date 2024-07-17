#include "editor/editor.h"

XKEINEDITOR_API std::shared_ptr<YrEditor> gYrEditor;

class YrEditorWindow_Impl
{
public:
    YrEditorWindow_Impl(YrEditorWindow* window) : window(window)
    {
        gYrEditor->windows.push_back(std::unique_ptr<YrEditorWindow>(window));
    }
    ~YrEditorWindow_Impl()
    {
        Close();
        if (auto iter = std::find_if(gYrEditor->windows.begin(), gYrEditor->windows.end(), [=](auto& ptr) { return ptr.get() == window; }); iter != gYrEditor->windows.end())
        {
            gYrEditor->windows.erase(iter);
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
