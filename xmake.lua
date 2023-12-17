-- set minimum xmake version
set_xmakever("2.7.8")

-- set project
set_project("OpenAnimationReplacer-DialoguePlugin")
set_version("1.0.0")
set_license("gplv3")
set_languages("c++20")
set_optimize("faster")
set_warnings("allextra", "error")

-- set allowed
set_allowedarchs("windows|x64")
set_allowedmodes("debug", "releasedbg")

-- set defaults
set_defaultarchs("windows|x64")
set_defaultmode("releasedbg")

-- add rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- set policies
set_policy("package.requires_lock", true)

-- require packages
add_requires("commonlibsse-ng", { configs = { skyrim_vr = true } })

-- targets
target("OpenAnimationReplacer-DialoguePlugin")
    -- add packages to target
    add_packages("fmt", "spdlog", "commonlibsse-ng")

    -- add commonlibsse-ng plugin
    add_rules("@commonlibsse-ng/plugin", {
        name = "OpenAnimationReplacer-DialoguePlugin",
        author = "Nonameron",
        description = "SKSE64 plugin adding dialogue conditions to OpenAnimationReplacer's API"
    })

    -- add src files
    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/pch.h")

    -- copy build files to MODS or SKYRIM paths
    after_build(function(target)
        local copy = function(env, ext)
            for _, env in pairs(env:split(";")) do
                if os.exists(env) then
                    local plugins = path.join(env, ext, "SKSE/Plugins")
                    os.mkdir(plugins)
                    os.trycp(target:targetfile(), plugins)
                    os.trycp(target:symbolfile(), plugins)
                end
            end
        end
        copy("D:/Downloads/Skyrim/Own mods/", "OAR DialoguePlugin")
        copy("D:/Downloads/Skyrim/Mod Organizer 2/mods/", "OpenAnimationReplacer - Dialogue plugin")
    end)

