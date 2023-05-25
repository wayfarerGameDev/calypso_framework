const Builder = @import("std").build.Builder;

pub fn build(b: *Builder) void {
    const mode = b.standardReleaseOptions();

    const sdl2Path = "dependencies/sdl2_64";
    const gladPath = "dependencies/glad";
    const glfwPath = "dependencies/glfw_64";

    const sourceFiles = b.addAllFile("source/example_render_pipeline", ".c");
    const gladFiles = b.addAllFile(gladPath ++ "/source", ".c");
    _ = gladFiles;

    const includeDirs = [_][]const u8{
        sdl2Path,
        gladPath ++ "/include",
        glfwPath ++ "/include",
    };

    const libDirs = [_][]const u8{
        sdl2Path ++ "/lib",
        glfwPath ++ "/lib",
    };

    var exe = b.addExecutable("app", sourceFiles);
    exe.setTarget(mode);
    exe.setIncludeDirs(includeDirs);
    exe.setLinkDirs(libDirs);

    exe.linkLibC();
    exe.linkSystemLibrary("mingw32");
    exe.linkSystemLibrary("SDL2main");
    exe.linkSystemLibrary("SDL2");
    exe.linkSystemLibrary("SDL2_ttf");
    exe.linkSystemLibrary("SDL2_image");
    exe.linkSystemLibrary("glfw3");
    exe.linkSystemLibrary("gdi32");

    if (b.os.tag == .windows) {
        exe.addCommand("cmd", "/c", "cls");
    }

    exe.install();
}
