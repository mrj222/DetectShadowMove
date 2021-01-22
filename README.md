# DetectShadowMove
Lab3 for CompNet

## Introduction

This project focus on shadowMove in APT detection. We add kernel module to send packets with identifier, and deploy our sketch algorithm in P4-switches to detect possible socket duplication. The following tasks are done to simulate and evaluate our work.

* `cpu`: we conduct experiments of our detecting algorithm in CPU for evaluation.
* `mininet`: we do simulation on Mininet for evaluation.
* `linux_module`: we add linux kernel module for real client and server to send packets with identifier
* `tofino`: we implement our algorithm on Tofino switch. The p4 code is not included here though.

## Usage

The usage of code is included in `README.md` in each directory. 