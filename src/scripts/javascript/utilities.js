/*
* Tencent is pleased to support the open source community by making Puerts available.
* Copyright (C) 2020 THL A29 Limited, a Tencent company.  All rights reserved.
* Puerts is licensed under the BSD 3-Clause License, except for the third-party components listed in the file 'LICENSE' which may be subject to their corresponding license terms.
* This file is subject to the terms and conditions defined in file 'LICENSE', which is part of this source code package.
*/

var global = global || (function () { return this; }());
(function (global) {
    "use strict";
    
    global.getCppTypeName = function (type) {
        return type.__ClassName;
    }
    
    function ref(x) {
        return [x];
    }

    function unref(r) {
        return r[0];
    }
    
    function setref(x, val) {
        x[0] = val;
    }
    
    puerts.$ref = ref;
    puerts.$unref = unref;
    puerts.$set = setref;

    // Keep registered functions alive: the registry stores raw pointers, so a collected JS wrapper would destroy the underlying C++ object and leave a dangling pointer (see doc/script_function.md §4.4).
    var persistentScriptFunctions = global.__scriptFunctionPersistentObjs || (global.__scriptFunctionPersistentObjs = []);

    // public static void RegisterFunction(char const * category, char const * name, ScriptFunctionBase * func)
    global.RegisterScriptFunction = function (category, name, func) {
        YrExtCore.ScriptFunctionRegister.RegisterFunction(category, name, func);
        persistentScriptFunctions.push(func);
        return func;
    }
}(global));
