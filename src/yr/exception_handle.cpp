#include "yr_hook.h"
#include "runtime/logger/logger.h"
#include "debug_util.h"
#include "yr/patch/patch.h"
#include "yr/yr_hook_diagnostic.h"
#include <Unsorted.h>
#include <Surface.h>
#include <filesystem>
#include <fstream>
#include <chrono>

namespace fs = std::filesystem;

void TakeScreenShot(fs::path& errorDir)
{
	RECT Viewport = {};
	if(Imports::GetWindowRect(Game::hWnd, &Viewport)) {
		POINT TL = {Viewport.left, Viewport.top}, BR = {Viewport.right, Viewport.bottom};
		if(Imports::ClientToScreen(Game::hWnd, &TL) && Imports::ClientToScreen(Game::hWnd, &BR)) {
			RectangleStruct ClipRect = {TL.x, TL.y, Viewport.right + 1, Viewport.bottom + 1};

			DSurface * Surface = DSurface::Primary;

			int width = Surface->GetWidth();
			int height = Surface->GetHeight();

			size_t arrayLen = width * height;

			if(width < ClipRect.Width) {
				ClipRect.Width = width;
			}
			if(height < ClipRect.Height) {
				ClipRect.Height = height;
			}

//			RectangleStruct DestRect = {0, 0, width, height};
//			Surface->BlitPart(&DestRect, DSurface::Primary, &ClipRect, 0, 1);

			if(WORD * buffer = reinterpret_cast<WORD *>(Surface->Lock(0, 0)))
            {
                fs::path imgPath = errorDir / "screenshot.bmp";
                std::ofstream screenShot(imgPath, std::ofstream::out | std::ofstream::binary);

				#pragma pack(push, 1)
				struct bmpfile_full_header {
					unsigned char magic[2];
					DWORD filesz;
					WORD creator1;
					WORD creator2;
					DWORD bmp_offset;
					DWORD header_sz;
					DWORD width;
					DWORD height;
					WORD nplanes;
					WORD bitspp;
					DWORD compress_type;
					DWORD bmp_bytesz;
					DWORD hres;
					DWORD vres;
					DWORD ncolors;
					DWORD nimpcolors;
					DWORD R; //
					DWORD G; //
					DWORD B; //
				} h;
				#pragma pack(pop)

				h.magic[0] = 'B';
				h.magic[1] = 'M';

				h.creator1 = h.creator2 = 0;

				h.header_sz = 40;
				h.width = width;
				h.height = -height; // magic! no need to reverse rows this way
				h.nplanes = 1;
				h.bitspp = 16;
				h.compress_type = BI_BITFIELDS;
				h.bmp_bytesz = arrayLen * 2;
				h.hres = 4000;
				h.vres = 4000;
				h.ncolors = h.nimpcolors = 0;

				h.R = 0xF800;
				h.G = 0x07E0;
				h.B = 0x001F; // look familiar?

				h.bmp_offset = sizeof(h);
				h.filesz = h.bmp_offset + h.bmp_bytesz;

                screenShot.write((const char*)&h, sizeof(h));
				std::unique_ptr<WORD[]> pixelData(new WORD[arrayLen]);
				WORD *pixels = pixelData.get();
				int pitch = Surface->VideoSurfaceDescription->lPitch;
				for(int r = 0; r < height; ++r) {
					memcpy(pixels, reinterpret_cast<void *>(buffer), width * 2);
					pixels += width;
					buffer += pitch / 2; // /2 because buffer is a WORD * and pitch is in bytes
				}

                screenShot.write((const char*)pixelData.get(), arrayLen * 2);
				screenShot.flush();
				Surface->Unlock();
			}
		}
	}
}

SYRINGE_PATCH(0x4C8FE0, Exception_Handler, 9)
{
	GET(LPEXCEPTION_POINTERS, pExs, EDX);
    std::string* stackTrace = nullptr;
    ExceptionFilterGetInfo(pExs, stackTrace);
    gLogger->error("[Fatal Error!] stack trace : {}", *stackTrace);
    
    DebugPatchCallInfo info = GetDebugPatchCallInfo();
    gLogger->error("patch calling list:");
    for (auto &&data : info.callingList)
    {
        gLogger->error("-- {} - {}", (void*)data->hookAddr, data->hookFunc);
    }
    gLogger->error("patch called list:");
    for (auto &&data : info.calledList)
    {
        gLogger->error("-- {} - {}", (void*)data->hookAddr, data->hookFunc);
    }

    gLogger->flush();
    delete stackTrace;
    
    fs::path errorDir = fs::path("debug") / "yrextcore" / std::format("crash_{:%F-%H-%M-%S}", std::chrono::system_clock::now());
    fs::create_directory(errorDir);
    TakeScreenShot(errorDir);
    fs::copy_file(fs::path("debug") / "yrextcore" / "yr_extcore.log" , errorDir / "yr_extcore_crash.log");

    return 0;
}