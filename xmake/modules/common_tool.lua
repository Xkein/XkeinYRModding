
function get_thirdparty_path(module)
    return "$(projectdir)/3rdparty/" .. module
end

function get_config_path(module)
    return "$(buildir)/config/"..module
end

