/// <reference path = "../index.d.ts"/>
declare module "gainput" {
import { $Ref } from "puerts";
import { CDTimerClass, AbstractClass, AbstractTypeClass, CCINIClass, LandType, Action, AircraftClass, AircraftTypeClass, AnimClass, AnimTypeClass, BuildingClass, BuildingTypeClass, BulletClass, BulletTypeClass, DamageState, DirType, FireError, GadgetClass, GadgetFlag, HouseClass, HouseTypeClass, InfantryClass, InfantryTypeClass, IStream, KeyModifier, MissionClass, ObjectClass, RulesClass, SuperClass, SuperWeaponTypeClass, TActionClass, TechnoClass, TechnoTypeClass, TerrainClass, TerrainTypeClass, TriggerClass, UnitClass, UnitTypeClass, Vector3D, WarheadTypeClass, WeaponTypeClass, ThemeClass, ThemeControl, Vector2D, AbstractType, FootClass, PassengersClass } from "YRpp";
import { AKRESULT } from "Wwise";
// Maps user buttons to device buttons.
// This is the interface that should be used to get input. You can have several maps that are used
// simultaneously or use different ones depending on game state. The user button IDs have to be unique per input map.
// InputMap uses the provided InputManager to get devices inputs and process them into user-mapped inputs. After creating 
// an InputMap, you should map some device buttons to user buttons (using MapBool() or MapFloat()). User buttons are identified 
// by an ID provided by you. In order to ensure their uniqueness, it's a good idea to define an enum containing all your user buttons
// for any given InputMap. It's of course possible to map multiple different device button to one user button.
// After a user button has been mapped, you can query its state by calling one of the several GetBool* and GetFloat* functions. The
// result will depend on the mapped device button(s) and the policy (set using SetUserButtonPolicy()).
// gainput::InputMap
class gainput__InputMap
{
    // Initializes the map.
    // 
    // @param manager The input manager used to get device inputs.
    // @param name The name for the input map (optional). If a name is provided, it is copied to an internal buffer.
    // @param allocator The allocator to be used for all memory allocations.
    // public InputMap(gainput::InputManager& manager, char const * name = 0, gainput::Allocator& allocator = GetDefaultAllocator())
    constructor(manager_0 : any, name_1 : string, allocator_2 : any);
    // Clears all mapped inputs.
    // public void Clear()
    Clear() : void;
    // Returns the input manager this input map uses.
    // public gainput::InputManager const * GetManager() const
    GetManager() : any;
    // Returns the map's name, if any.
    // 
    // @return The map's name or 0 if no name was set.
    // public char const * GetName() const
    GetName() : string;
    // Returns the map's auto-generated ID (that should not be used outside of the library).
    // public unsigned int GetId() const
    GetId() : number;
    // Maps a bool-type button.
    // 
    // @param userButton The user ID for this mapping.
    // @param device The device's ID of the device button to be mapped.
    // @param deviceButton The ID of the device button to be mapped.
    // @return true if the mapping was created.
    // public bool MapBool(UserButtonId userButton, DeviceId device, DeviceButtonId deviceButton)
    MapBool(userButton_0 : any, device_1 : any, deviceButton_2 : any) : boolean;
    // Maps a float-type button, possibly to a custom range.
    // 
    // @param userButton The user ID for this mapping.
    // @param device The device's ID of the device button to be mapped.
    // @param deviceButton The ID of the device button to be mapped.
    // @param min Optional minimum value of the mapped button.
    // @param max Optional maximum value of the mapped button.
    // @param filterFunc Optional filter functions that modifies the device button value.
    // @param filterUserData Optional user data pointer that is passed to filterFunc.
    // @return true if the mapping was created.
    // public bool MapFloat(UserButtonId userButton, DeviceId device, DeviceButtonId deviceButton, float min = 0.0f, float max = 1.0f, FilterFunc_T filterFunc = 0, void * filterUserData = 0)
    MapFloat(userButton_0 : any, device_1 : any, deviceButton_2 : any, min_3 : number, max_4 : number, filterFunc_5 : any, filterUserData_6 : ArrayBuffer) : boolean;
    // Removes all mappings for the given user button.
    // public void Unmap(UserButtonId userButton)
    Unmap(userButton_0 : any) : void;
    // Returns if the given user button has any mappings.
    // public bool IsMapped(UserButtonId userButton) const
    IsMapped(userButton_0 : any) : boolean;
    // Gets all device buttons mapped to the given user button.
    // 
    // @param userButton The user button ID of the button to return all mappings for.
    // @param outButtons An array with maxButtonCount fields to receive the device buttons that are mapped.
    // @param maxButtonCount The number of fields in outButtons.
    // @return The number of device buttons written to outButtons.
    // public unsigned int GetMappings(UserButtonId userButton, gainput::DeviceButtonSpec * outButtons, unsigned int maxButtonCount) const
    GetMappings(userButton_0 : any, outButtons_1 : any, maxButtonCount_2 : number) : number;
    // Sets how a user button handles inputs from multiple device buttons.
    // 
    // @return true if the policy was set, false otherwise (i.e. the user button doesn't exist).
    // public bool SetUserButtonPolicy(UserButtonId userButton, UserButtonPolicy policy)
    SetUserButtonPolicy(userButton_0 : any, policy_1 : any) : boolean;
    // Sets a dead zone for a float-type button.
    // If a dead zone is set for a button anything less or equal to the given value will be treated
    // as 0.0f. The absolute input value is used in order to determine if the input value falls within the dead
    // zone (i.e. with a dead zone of 0.2f, both -0.1f and 0.1f will result in 0.0f).
    // 
    // @param userButton The user button's ID.
    // @param deadZone The dead zone to be set.
    // @return true if the dead zone was set, false otherwise (i.e. the user button doesn't exist).
    // public bool SetDeadZone(UserButtonId userButton, float deadZone)
    SetDeadZone(userButton_0 : any, deadZone_1 : number) : boolean;
    // Returns the bool state of a user button.
    // public bool GetBool(UserButtonId userButton) const
    GetBool(userButton_0 : any) : boolean;
    // Returns if the user button is newly down.
    // public bool GetBoolIsNew(UserButtonId userButton) const
    GetBoolIsNew(userButton_0 : any) : boolean;
    // Returns the bool state of a user button from the previous frame.
    // public bool GetBoolPrevious(UserButtonId userButton) const
    GetBoolPrevious(userButton_0 : any) : boolean;
    // Returns if the user button has been released.
    // public bool GetBoolWasDown(UserButtonId userButton) const
    GetBoolWasDown(userButton_0 : any) : boolean;
    // Returns the float state of a user button.
    // public float GetFloat(UserButtonId userButton) const
    GetFloat(userButton_0 : any) : number;
    // Returns the float state of a user button from the previous frame.
    // public float GetFloatPrevious(UserButtonId userButton) const
    GetFloatPrevious(userButton_0 : any) : number;
    // Returns the delta between the previous and the current frame of the float state of the given user button.
    // public float GetFloatDelta(UserButtonId userButton) const
    GetFloatDelta(userButton_0 : any) : number;
    // Gets the name of the device button mapped to the given user button.
    // 
    // @param userButton ID of the user button.
    // @param buffer A char-buffer to receive the button name.
    // @param bufferLength Length of the buffer receiving the button name in bytes.
    // @return The number of bytes written to buffer (includes the trailing 
    // \
    // 0).
    // public unsigned int GetUserButtonName(UserButtonId userButton, char * buffer, unsigned int bufferLength) const
    GetUserButtonName(userButton_0 : any, buffer_1 : string, bufferLength_2 : number) : number;
    // Returns the user button ID the given device button is mapped to.
    // This function iterates over all mapped buttons and therefore shouldn't be used in a performance critical
    // situation.
    // 
    // @param device The device's ID of the device button to be checked.
    // @param deviceButton The ID of the device button to be checked.
    // @return The user button ID the device button is mapped to or InvalidDeviceButtonId if the device button is not mapped.
    // public UserButtonId GetUserButtonId(DeviceId device, DeviceButtonId deviceButton) const
    GetUserButtonId(device_0 : any, deviceButton_1 : any) : any;
    // Registers a listener to be notified when a button state changes.
    // If there are listeners registered, all input devices will have to record their state changes. This incurs extra runtime costs.
    // public ListenerId AddListener(gainput::MappedInputListener * listener)
    AddListener(listener_0 : any) : any;
    // De-registers the given listener.
    // public void RemoveListener(ListenerId listenerId)
    RemoveListener(listenerId_0 : any) : void;
    // Sorts the list of listeners which controls the order in which listeners are called.
    // The order of listeners may be important as the functions being called to notify a listener of a state change can control if
    // the state change will be passed to any consequent listeners. Call this function whenever listener priorites have changed. It
    // is automatically called by AddListener() and RemoveListener().
    // public void ReorderListeners()
    ReorderListeners() : void;
}

class gainput {
}
// All valid device buttons for InputDeviceKeyboard.
// gainput::Key
enum Key {
    // KeyEscape = 
    KeyEscape = 0,
    // KeyF1 = 
    KeyF1 = 1,
    // KeyF2 = 
    KeyF2 = 2,
    // KeyF3 = 
    KeyF3 = 3,
    // KeyF4 = 
    KeyF4 = 4,
    // KeyF5 = 
    KeyF5 = 5,
    // KeyF6 = 
    KeyF6 = 6,
    // KeyF7 = 
    KeyF7 = 7,
    // KeyF8 = 
    KeyF8 = 8,
    // KeyF9 = 
    KeyF9 = 9,
    // KeyF10 = 
    KeyF10 = 10,
    // KeyF11 = 
    KeyF11 = 11,
    // KeyF12 = 
    KeyF12 = 12,
    // KeyF13 = 
    KeyF13 = 13,
    // KeyF14 = 
    KeyF14 = 14,
    // KeyF15 = 
    KeyF15 = 15,
    // KeyF16 = 
    KeyF16 = 16,
    // KeyF17 = 
    KeyF17 = 17,
    // KeyF18 = 
    KeyF18 = 18,
    // KeyF19 = 
    KeyF19 = 19,
    // KeyPrint = 
    KeyPrint = 20,
    // KeyScrollLock = 
    KeyScrollLock = 21,
    // KeyBreak = 
    KeyBreak = 22,
    // KeySpace = 0x0020
    KeySpace = 32,
    // KeyApostrophe = 0x0027
    KeyApostrophe = 39,
    // KeyComma = 0x002c
    KeyComma = 44,
    // KeyMinus = 0x002d
    KeyMinus = 45,
    // KeyPeriod = 0x002e
    KeyPeriod = 46,
    // KeySlash = 0x002f
    KeySlash = 47,
    // Key0 = 0x0030
    Key0 = 48,
    // Key1 = 0x0031
    Key1 = 49,
    // Key2 = 0x0032
    Key2 = 50,
    // Key3 = 0x0033
    Key3 = 51,
    // Key4 = 0x0034
    Key4 = 52,
    // Key5 = 0x0035
    Key5 = 53,
    // Key6 = 0x0036
    Key6 = 54,
    // Key7 = 0x0037
    Key7 = 55,
    // Key8 = 0x0038
    Key8 = 56,
    // Key9 = 0x0039
    Key9 = 57,
    // KeySemicolon = 0x003b
    KeySemicolon = 59,
    // KeyLess = 0x003c
    KeyLess = 60,
    // KeyEqual = 0x003d
    KeyEqual = 61,
    // KeyA = 0x0041
    KeyA = 65,
    // KeyB = 0x0042
    KeyB = 66,
    // KeyC = 0x0043
    KeyC = 67,
    // KeyD = 0x0044
    KeyD = 68,
    // KeyE = 0x0045
    KeyE = 69,
    // KeyF = 0x0046
    KeyF = 70,
    // KeyG = 0x0047
    KeyG = 71,
    // KeyH = 0x0048
    KeyH = 72,
    // KeyI = 0x0049
    KeyI = 73,
    // KeyJ = 0x004a
    KeyJ = 74,
    // KeyK = 0x004b
    KeyK = 75,
    // KeyL = 0x004c
    KeyL = 76,
    // KeyM = 0x004d
    KeyM = 77,
    // KeyN = 0x004e
    KeyN = 78,
    // KeyO = 0x004f
    KeyO = 79,
    // KeyP = 0x0050
    KeyP = 80,
    // KeyQ = 0x0051
    KeyQ = 81,
    // KeyR = 0x0052
    KeyR = 82,
    // KeyS = 0x0053
    KeyS = 83,
    // KeyT = 0x0054
    KeyT = 84,
    // KeyU = 0x0055
    KeyU = 85,
    // KeyV = 0x0056
    KeyV = 86,
    // KeyW = 0x0057
    KeyW = 87,
    // KeyX = 0x0058
    KeyX = 88,
    // KeyY = 0x0059
    KeyY = 89,
    // KeyZ = 0x005a
    KeyZ = 90,
    // KeyBracketLeft = 0x005b
    KeyBracketLeft = 91,
    // KeyBackslash = 0x005c
    KeyBackslash = 92,
    // KeyBracketRight = 0x005d
    KeyBracketRight = 93,
    // KeyGrave = 0x0060
    KeyGrave = 96,
    // KeyLeft = 
    KeyLeft = 97,
    // KeyRight = 
    KeyRight = 98,
    // KeyUp = 
    KeyUp = 99,
    // KeyDown = 
    KeyDown = 100,
    // KeyInsert = 
    KeyInsert = 101,
    // KeyHome = 
    KeyHome = 102,
    // KeyDelete = 
    KeyDelete = 103,
    // KeyEnd = 
    KeyEnd = 104,
    // KeyPageUp = 
    KeyPageUp = 105,
    // KeyPageDown = 
    KeyPageDown = 106,
    // KeyNumLock = 
    KeyNumLock = 107,
    // KeyKpEqual = 
    KeyKpEqual = 108,
    // KeyKpDivide = 
    KeyKpDivide = 109,
    // KeyKpMultiply = 
    KeyKpMultiply = 110,
    // KeyKpSubtract = 
    KeyKpSubtract = 111,
    // KeyKpAdd = 
    KeyKpAdd = 112,
    // KeyKpEnter = 
    KeyKpEnter = 113,
    // 0
    // KeyKpInsert = 
    KeyKpInsert = 114,
    // 1
    // KeyKpEnd = 
    KeyKpEnd = 115,
    // 2
    // KeyKpDown = 
    KeyKpDown = 116,
    // 3
    // KeyKpPageDown = 
    KeyKpPageDown = 117,
    // 4
    // KeyKpLeft = 
    KeyKpLeft = 118,
    // 5
    // KeyKpBegin = 
    KeyKpBegin = 119,
    // 6
    // KeyKpRight = 
    KeyKpRight = 120,
    // 7
    // KeyKpHome = 
    KeyKpHome = 121,
    // 8
    // KeyKpUp = 
    KeyKpUp = 122,
    // 9
    // KeyKpPageUp = 
    KeyKpPageUp = 123,
    // ,
    // KeyKpDelete = 
    KeyKpDelete = 124,
    // KeyBackSpace = 
    KeyBackSpace = 125,
    // KeyTab = 
    KeyTab = 126,
    // KeyReturn = 
    KeyReturn = 127,
    // KeyCapsLock = 
    KeyCapsLock = 128,
    // KeyShiftL = 
    KeyShiftL = 129,
    // KeyCtrlL = 
    KeyCtrlL = 130,
    // KeySuperL = 
    KeySuperL = 131,
    // KeyAltL = 
    KeyAltL = 132,
    // KeyAltR = 
    KeyAltR = 133,
    // KeySuperR = 
    KeySuperR = 134,
    // KeyMenu = 
    KeyMenu = 135,
    // KeyCtrlR = 
    KeyCtrlR = 136,
    // KeyShiftR = 
    KeyShiftR = 137,
    // KeyBack = 
    KeyBack = 138,
    // KeySoftLeft = 
    KeySoftLeft = 139,
    // KeySoftRight = 
    KeySoftRight = 140,
    // KeyCall = 
    KeyCall = 141,
    // KeyEndcall = 
    KeyEndcall = 142,
    // KeyStar = 
    KeyStar = 143,
    // KeyPound = 
    KeyPound = 144,
    // KeyDpadCenter = 
    KeyDpadCenter = 145,
    // KeyVolumeUp = 
    KeyVolumeUp = 146,
    // KeyVolumeDown = 
    KeyVolumeDown = 147,
    // KeyPower = 
    KeyPower = 148,
    // KeyCamera = 
    KeyCamera = 149,
    // KeyClear = 
    KeyClear = 150,
    // KeySymbol = 
    KeySymbol = 151,
    // KeyExplorer = 
    KeyExplorer = 152,
    // KeyEnvelope = 
    KeyEnvelope = 153,
    // KeyEquals = 
    KeyEquals = 154,
    // KeyAt = 
    KeyAt = 155,
    // KeyHeadsethook = 
    KeyHeadsethook = 156,
    // KeyFocus = 
    KeyFocus = 157,
    // KeyPlus = 
    KeyPlus = 158,
    // KeyNotification = 
    KeyNotification = 159,
    // KeySearch = 
    KeySearch = 160,
    // KeyMediaPlayPause = 
    KeyMediaPlayPause = 161,
    // KeyMediaStop = 
    KeyMediaStop = 162,
    // KeyMediaNext = 
    KeyMediaNext = 163,
    // KeyMediaPrevious = 
    KeyMediaPrevious = 164,
    // KeyMediaRewind = 
    KeyMediaRewind = 165,
    // KeyMediaFastForward = 
    KeyMediaFastForward = 166,
    // KeyMute = 
    KeyMute = 167,
    // KeyPictsymbols = 
    KeyPictsymbols = 168,
    // KeySwitchCharset = 
    KeySwitchCharset = 169,
    // KeyForward = 
    KeyForward = 170,
    // KeyExtra1 = 
    KeyExtra1 = 171,
    // KeyExtra2 = 
    KeyExtra2 = 172,
    // KeyExtra3 = 
    KeyExtra3 = 173,
    // KeyExtra4 = 
    KeyExtra4 = 174,
    // KeyExtra5 = 
    KeyExtra5 = 175,
    // KeyExtra6 = 
    KeyExtra6 = 176,
    // KeyFn = 
    KeyFn = 177,
    // KeyCircumflex = 
    KeyCircumflex = 178,
    // KeySsharp = 
    KeySsharp = 179,
    // KeyAcute = 
    KeyAcute = 180,
    // KeyAltGr = 
    KeyAltGr = 181,
    // KeyNumbersign = 
    KeyNumbersign = 182,
    // KeyUdiaeresis = 
    KeyUdiaeresis = 183,
    // KeyAdiaeresis = 
    KeyAdiaeresis = 184,
    // KeyOdiaeresis = 
    KeyOdiaeresis = 185,
    // KeySection = 
    KeySection = 186,
    // KeyAring = 
    KeyAring = 187,
    // KeyDiaeresis = 
    KeyDiaeresis = 188,
    // KeyTwosuperior = 
    KeyTwosuperior = 189,
    // KeyRightParenthesis = 
    KeyRightParenthesis = 190,
    // KeyDollar = 
    KeyDollar = 191,
    // KeyUgrave = 
    KeyUgrave = 192,
    // KeyAsterisk = 
    KeyAsterisk = 193,
    // KeyColon = 
    KeyColon = 194,
    // KeyExclam = 
    KeyExclam = 195,
    // KeyBraceLeft = 
    KeyBraceLeft = 196,
    // KeyBraceRight = 
    KeyBraceRight = 197,
    // KeySysRq = 
    KeySysRq = 198,
    // KeyCount_ = 
    KeyCount_ = 199,
}
}
