# CI/CD Pipeline with GitHub Actions

This document outlines the setup and advantages of implementing a CI/CD pipeline using GitHub Actions for the R-Type project. Additionally, it explains certain choices made about the pipeline.

## Purpose

Creating a CI/CD pipeline using GitHub Actions ensures that the project is continuously integrated and delivered. This process automates the building of the code, ensuring that every change is validated.

## Advantages

1. **Consistent Builds**: Ensure that the project builds correctly in a clean environment every time, reducing "it works on my machine" issues.
2. **Faster Feedback**: Get immediate feedback on the status of the code, reducing the time to detect and fix issues.
3. **Improved Collaboration**: Team members can see the status of the project and understand the impact of their changes.
4. **Cross-Platform Compilation**: Automate the process of building and testing the project on multiple platforms, ensuring compatibility and reducing platform-specific issues.

## Caching vcpkg Dependencies

Caching vcpkg dependencies in the CI/CD process offers several benefits:

1. **Speed**: Reduces the time required to install dependencies by reusing previously downloaded packages.
2. **Efficiency**: Minimizes the load on package servers and reduces network bandwidth usage.
3. **Consistency**: Ensures that the same versions of dependencies are used across different builds, reducing the risk of inconsistencies.
