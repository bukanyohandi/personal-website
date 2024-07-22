---
title: "Multiple Dispatch Micro-Kernels for IREE"
date: "2024-05-19"
author: "Yohandi"
tags: [compiler, machine-learning, optimization, parallel-programming, project]
---

This work details the optimization of matrix multiplication operations for the open-source ML compiler and runtime IREE through the utilization of multiple dispatch micro-kernels. We demonstrate the improvement in performance by performing training and inference of a ResNet50 MNIST model imported from TensorFlow compiled to run on our modified IREE runtime. Our results show a 300x performance improvement over running the same model with default settings on the stock IREE VM runtime. The primary contribution of this work is the incorporation of multiple dispatch for micro-kernels into the IREE VM runtime, resulting in up to a 74\% speed-up over the stock IREE with only single dispatch capability.

[multiple-dispatch-micro-kernels](/posts/resources/multiple-dispatch-micro-kernels/multiple-dispatch-micro-kernels.pdf)

All implementations are available [here](https://github.com/iree-org/iree).