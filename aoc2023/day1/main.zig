const std = @import("std");

pub fn main() void {
    const dir = std.fs.cwd();
    var input = std.fs.Dir.openFile(dir, "~/stuff/projects/aoc2023/day1/input", .{});
    defer input.close();
    var buf_reader = std.io.bufferedReader(input.reader());
    var in_stream = buf_reader.reader();
    var buf: [1024]u8 = undefined;

    while (try in_stream.readUntilDelimiterOrEof(&buf, '\n')) |line| {
        std.debug.print("{}", .{line});
    }
}
