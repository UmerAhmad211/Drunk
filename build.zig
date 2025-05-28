const std = @import("std");
const cxx_src_files = [_][]const u8{
    "src/main.cpp",
    "lib/fndtion.cpp",
    "lib/init.cpp",
    "lib/stock.cpp",
    "lib/tableau.cpp",
    "lib/util.cpp",
};

const cxx_flags = [_][]const u8{
    "-std=c++17",
    "-Oz",
    "-flto",
    "-march=native",
    "-ffast-math",
};

pub fn build(b: *std.Build) void {
    const exe = b.addExecutable(.{
        .name = "game",
        .target = b.graph.host,
        .optimize = .ReleaseSmall,
        .strip = true,
        .unwind_tables = .none,
    });
    exe.addCSourceFiles(.{ .files = &cxx_src_files, .flags = &cxx_flags });
    exe.linkSystemLibrary("raylib");
    exe.linkLibCpp();
    b.installArtifact(exe);
}
