// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "ParallelSum",
    products: [
        .library(
            name: "ParallelSum",
            type: .static,
            targets: ["ParallelSum"]),
    ],
    targets: [
        .target(
            name: "ParallelSum",
            path: "Sources/ParallelSum",
            exclude: [],
            sources: ["ParallelSum.cpp", "ParallelSum.h"],
            publicHeadersPath: "."
        ),
    ],
    cxxLanguageStandard: .cxx11
)
