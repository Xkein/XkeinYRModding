/// <reference path = "../index.d.ts"/>
declare module "Wwise" {
import { $Ref } from "puerts";
import { CDTimerClass, AbstractClass, AbstractTypeClass, CCINIClass, LandType, Action, AircraftClass, AircraftTypeClass, AnimClass, AnimTypeClass, BuildingClass, BuildingTypeClass, BulletClass, BulletTypeClass, DamageState, DirType, FireError, GadgetClass, GadgetFlag, HouseClass, HouseTypeClass, InfantryClass, InfantryTypeClass, IStream, KeyModifier, MissionClass, ObjectClass, RulesClass, SuperClass, SuperWeaponTypeClass, TActionClass, TechnoClass, TechnoTypeClass, TerrainClass, TerrainTypeClass, TriggerClass, UnitClass, UnitTypeClass, Vector3D, WarheadTypeClass, WeaponTypeClass, ThemeClass, ThemeControl, Vector2D, AbstractType, FootClass, PassengersClass } from "YRpp";

class Wwise {
}
// Standard function call result.
// AKRESULT
enum AKRESULT {
    // This feature is not implemented.
    // AK_NotImplemented = 0
    AK_NotImplemented = 0,
    // The operation was successful.
    // AK_Success = 1
    AK_Success = 1,
    // The operation failed.
    // AK_Fail = 2
    AK_Fail = 2,
    // The operation succeeded partially.
    // AK_PartialSuccess = 3
    AK_PartialSuccess = 3,
    // Incompatible formats
    // AK_NotCompatible = 4
    AK_NotCompatible = 4,
    // The stream is already connected to another node.
    // AK_AlreadyConnected = 5
    AK_AlreadyConnected = 5,
    // The provided file is the wrong format or unexpected values causes the file to be invalid.
    // AK_InvalidFile = 7
    AK_InvalidFile = 7,
    // The file header is too large.
    // AK_AudioFileHeaderTooLarge = 8
    AK_AudioFileHeaderTooLarge = 8,
    // The maximum was reached.
    // AK_MaxReached = 9
    AK_MaxReached = 9,
    // The ID is invalid.
    // AK_InvalidID = 14
    AK_InvalidID = 14,
    // The ID was not found.
    // AK_IDNotFound = 15
    AK_IDNotFound = 15,
    // The InstanceID is invalid.
    // AK_InvalidInstanceID = 16
    AK_InvalidInstanceID = 16,
    // No more data is available from the source.
    // AK_NoMoreData = 17
    AK_NoMoreData = 17,
    // The StateGroup is not a valid channel.
    // AK_InvalidStateGroup = 20
    AK_InvalidStateGroup = 20,
    // The child already has a parent.
    // AK_ChildAlreadyHasAParent = 21
    AK_ChildAlreadyHasAParent = 21,
    // The language is invalid (applies to the Low-Level I/O).
    // AK_InvalidLanguage = 22
    AK_InvalidLanguage = 22,
    // It is not possible to add itself as its own child.
    // AK_CannotAddItselfAsAChild = 23
    AK_CannotAddItselfAsAChild = 23,
    // Something is not within bounds, check the documentation of the function returning this code.
    // AK_InvalidParameter = 31
    AK_InvalidParameter = 31,
    // The item could not be added because it was already in the list.
    // AK_ElementAlreadyInList = 35
    AK_ElementAlreadyInList = 35,
    // This path is not known.
    // AK_PathNotFound = 36
    AK_PathNotFound = 36,
    // Stuff in vertices before trying to start it
    // AK_PathNoVertices = 37
    AK_PathNoVertices = 37,
    // Only a running path can be paused.
    // AK_PathNotRunning = 38
    AK_PathNotRunning = 38,
    // Only a paused path can be resumed.
    // AK_PathNotPaused = 39
    AK_PathNotPaused = 39,
    // This path is already there.
    // AK_PathNodeAlreadyInList = 40
    AK_PathNodeAlreadyInList = 40,
    // This path is not there.
    // AK_PathNodeNotInList = 41
    AK_PathNodeNotInList = 41,
    // The consumer needs more.
    // AK_DataNeeded = 43
    AK_DataNeeded = 43,
    // The consumer does not need more.
    // AK_NoDataNeeded = 44
    AK_NoDataNeeded = 44,
    // The provider has available data.
    // AK_DataReady = 45
    AK_DataReady = 45,
    // The provider does not have available data.
    // AK_NoDataReady = 46
    AK_NoDataReady = 46,
    // Memory error.
    // AK_InsufficientMemory = 52
    AK_InsufficientMemory = 52,
    // The requested action was cancelled (not an error).
    // AK_Cancelled = 53
    AK_Cancelled = 53,
    // Trying to load a bank using an ID which is not defined.
    // AK_UnknownBankID = 54
    AK_UnknownBankID = 54,
    // Error while reading a bank.
    // AK_BankReadError = 56
    AK_BankReadError = 56,
    // Invalid switch type (used with the switch container)
    // AK_InvalidSwitchType = 57
    AK_InvalidSwitchType = 57,
    // Source format not known yet.
    // AK_FormatNotReady = 63
    AK_FormatNotReady = 63,
    // The bank version is not compatible with the current bank reader.
    // AK_WrongBankVersion = 64
    AK_WrongBankVersion = 64,
    // File not found.
    // AK_FileNotFound = 66
    AK_FileNotFound = 66,
    // Specified ID doesn't match a valid hardware device: either the device doesn't exist or is disabled.
    // AK_DeviceNotReady = 67
    AK_DeviceNotReady = 67,
    // The bank load failed because the bank is already loaded.
    // AK_BankAlreadyLoaded = 69
    AK_BankAlreadyLoaded = 69,
    // The effect on the node is rendered.
    // AK_RenderedFX = 71
    AK_RenderedFX = 71,
    // A routine needs to be executed on some CPU.
    // AK_ProcessNeeded = 72
    AK_ProcessNeeded = 72,
    // The executed routine has finished its execution.
    // AK_ProcessDone = 73
    AK_ProcessDone = 73,
    // The memory manager should have been initialized at this point.
    // AK_MemManagerNotInitialized = 74
    AK_MemManagerNotInitialized = 74,
    // The stream manager should have been initialized at this point.
    // AK_StreamMgrNotInitialized = 75
    AK_StreamMgrNotInitialized = 75,
    // The machine does not support SSE instructions (required on PC).
    // AK_SSEInstructionsNotSupported = 76
    AK_SSEInstructionsNotSupported = 76,
    // The system is busy and could not process the request.
    // AK_Busy = 77
    AK_Busy = 77,
    // Channel configuration is not supported in the current execution context.
    // AK_UnsupportedChannelConfig = 78
    AK_UnsupportedChannelConfig = 78,
    // Plugin media is not available for effect.
    // AK_PluginMediaNotAvailable = 79
    AK_PluginMediaNotAvailable = 79,
    // Sound was Not Allowed to play.
    // AK_MustBeVirtualized = 80
    AK_MustBeVirtualized = 80,
    // SDK command is too large to fit in the command queue.
    // AK_CommandTooLarge = 81
    AK_CommandTooLarge = 81,
    // A play request was rejected due to the MIDI filter parameters.
    // AK_RejectedByFilter = 82
    AK_RejectedByFilter = 82,
    // Detecting incompatibility between Custom platform of banks and custom platform of connected application
    // AK_InvalidCustomPlatformName = 83
    AK_InvalidCustomPlatformName = 83,
    // Plugin DLL could not be loaded, either because it is not found or one dependency is missing.
    // AK_DLLCannotLoad = 84
    AK_DLLCannotLoad = 84,
    // Plugin DLL search path could not be found.
    // AK_DLLPathNotFound = 85
    AK_DLLPathNotFound = 85,
    // No Java VM provided in AkInitSettings.
    // AK_NoJavaVM = 86
    AK_NoJavaVM = 86,
    // OpenSL returned an error.  Check error log for more details.
    // AK_OpenSLError = 87
    AK_OpenSLError = 87,
    // Plugin is not registered.  Make sure to implement a AK::PluginRegistration class for it and use AK_STATIC_LINK_PLUGIN in the game binary.
    // AK_PluginNotRegistered = 88
    AK_PluginNotRegistered = 88,
    // A pointer to audio data was not aligned to the platform's required alignment (check AkTypes.h in the platform-specific folder)
    // AK_DataAlignmentError = 89
    AK_DataAlignmentError = 89,
    // Incompatible Audio device.
    // AK_DeviceNotCompatible = 90
    AK_DeviceNotCompatible = 90,
    // Two Wwise objects share the same ID.
    // AK_DuplicateUniqueID = 91
    AK_DuplicateUniqueID = 91,
    // The Init bank was not loaded yet, the sound engine isn't completely ready yet.
    // AK_InitBankNotLoaded = 92
    AK_InitBankNotLoaded = 92,
    // The specified device ID does not match with any of the output devices that the sound engine is currently using.
    // AK_DeviceNotFound = 93
    AK_DeviceNotFound = 93,
    // Calling a function with a playing ID that is not known.
    // AK_PlayingIDNotFound = 94
    AK_PlayingIDNotFound = 94,
    // One parameter has a invalid float value such as NaN, INF or FLT_MAX.
    // AK_InvalidFloatValue = 95
    AK_InvalidFloatValue = 95,
    // Media file format unexpected
    // AK_FileFormatMismatch = 96
    AK_FileFormatMismatch = 96,
    // No distinct listener provided for AddOutput
    // AK_NoDistinctListener = 97
    AK_NoDistinctListener = 97,
    // Resource is in use and cannot be released.
    // AK_ResourceInUse = 99
    AK_ResourceInUse = 99,
    // Invalid bank type. The bank type was either supplied through a function call (e.g. LoadBank) or obtained from a bank loaded from memory.
    // AK_InvalidBankType = 100
    AK_InvalidBankType = 100,
    // Init() was called but that element was already initialized.
    // AK_AlreadyInitialized = 101
    AK_AlreadyInitialized = 101,
    // The component being used is not initialized. Most likely AK::SoundEngine::Init() was not called yet, or AK::SoundEngine::Term was called too early.
    // AK_NotInitialized = 102
    AK_NotInitialized = 102,
    // The file access permissions prevent opening a file.
    // AK_FilePermissionError = 103
    AK_FilePermissionError = 103,
    // Rare file error occured, as opposed to AK_FileNotFound or AK_FilePermissionError. This lumps all unrecognized OS file system errors.
    // AK_UnknownFileError = 104
    AK_UnknownFileError = 104,
    // When using StdStream, file operations can be blocking or not. When not blocking, operations need to be synchronized externally properly. If not, this error occurs.
    // AK_TooManyConcurrentOperations = 105
    AK_TooManyConcurrentOperations = 105,
    // The file requested was found and opened but is either 0 bytes long or not the expected size. This usually point toward a Low Level IO Hook implementation error.
    // AK_InvalidFileSize = 106
    AK_InvalidFileSize = 106,
    // Returned by functions to indicate to the caller the that the operation is done asynchronously. Used by Low Level IO Hook implementations when async operation are suppored by the hardware.
    // AK_Deferred = 107
    AK_Deferred = 107,
    // The combination of base path and file name exceeds maximum buffer lengths.
    // AK_FilePathTooLong = 108
    AK_FilePathTooLong = 108,
    // This method should not be called when the object is in its current state.
    // AK_InvalidState = 109
    AK_InvalidState = 109,
    // End of enum, invalid value.
    // AKRESULT_Last = 
    AKRESULT_Last = 110,
}
}
