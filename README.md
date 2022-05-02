[![GitHub issues](https://img.shields.io/github/issues/openair-collective/openair-violet?style=plastic)](https://github.com/openair-collective/openair-violet/issues) [![GitHub forks](https://img.shields.io/github/forks/openair-collective/openair-violet?style=plastic)](https://github.com/openair-collective/openair-violet/network) [![GitHub stars](https://img.shields.io/github/stars/openair-collective/openair-violet?style=plastic)](https://github.com/openair-collective/openair-violet/stargazers) [![GitHub license](https://img.shields.io/github/license/openair-collective/openair-violet?style=plastic)](https://github.com/openair-collective/openair-violet/blob/master/LICENSE)

<p align="center">
   <img width="550px" height="150px" title="Open-Air-Logo" src="./docs/assets/images/openair-logo.png">
</p>

---

# :seedling: openair-violet :seedling:

This repo is dedicated to the **openair-violet**, the worlds first open hardware *Direct Air Carbon Capture* ***(DACC)*** *Machine* :cactus: .

We are working off of the designs provided by ***`Dr Tao Wang`*** to produce the first designs for the **OpenAir Violet**.

This is *very much* a work in progress, below is the current diagram of what we are putting together.

![DACC Diagram](/./docs/assets/images/DACC.png/)

- [:seedling: openair-violet :seedling:](#seedling-openair-violet-seedling)
- [What is this Project?](#what-is-this-project)
  - [Where We are Going](#where-we-are-going)
  - [How to get involved?](#how-to-get-involved)
  - [How to setup](#how-to-setup)
  - [Main Project Folder](#main-project-folder)
  - [Source Files](#source-files)
  - [OpenAir CO2 Visualizer](#openair-co2-visualizer)
  - [List of Materials](#list-of-materials)
    - [Project Goals and To Do](#project-goals-and-to-do)

# What is this Project?

OpenAir Violet is an `open-source direct air carbon capture`, or `DACC`, prototype machine, and is just one of the OpenAir Collective’s Research & Development (R&D) projects. Inspired by the research of `Prof. Tao Wang` at `Zhejiang University`, Violet collects atmospheric CO2 by passing ambient air through a sorbent membrane material. The carbon is then captured and released from the sorbent using [Moisture Swing Technology](https://docs.google.com/document/d/15x6pYi-xJytPkurglT9BauONpkMiZNfhfKL4CRyjoe4/edit?usp=sharing).

## Where We are Going

The Violet project has near-term and long-term goals. `The ultimate goal of the Violet mission is to create a modular, small-scale DACC machine that is affordable, buildable, and distributable`. Empowering individuals to participate in carbon dioxide removal `CDR` technology.

**Current Goals**:

- Develop an affordable (*less than $2,000 per unit*) and ***DIY-buildable*** version of `Violet`
- Optimize the *moisture swing* sorbent compound to obtain ***1 kg/day CO2*** capture rate
- Facilitate `open-source collaboration` and share R&D ideas for continued development

**Future Goals**:

- Discover new applications for Violet and DACC technology
- Distribute Violet technology to individuals looking to contribute to it and advance it
- Solve key cost and technology barriers to widespread DACC implementation

## How to get involved?

Check out the [Materials](#list-of-materials) section to see what is required to get started building your own!

PCB's can be ordered from `JLCPCB` or `PCBWay`, or *made yourself*. The PCB files are still in prototype phase and we welcome any development ideas.

## How to setup

Setup is very straight forward, thankfully. You will need to purchase a few components before you begin:

---
<p align="center">
------------ BELOW IS AN EXAMPLE SETUP ----------------
</p>

---

***Materials for purchase***

1. Raspberrypi - any model
   1. Install Mosquito broker to the pi and connect it to your network
2. 12V submersable water pump
3. 3m or more of Vinyl tubing with 10mm ID and 13mm OD

***SETUP***

1. Acquire PCB and ESP32 (WROVER and WROOM has both been tested).
2. Acquire The remaining sensors and components - assemble
3. Plug ESP32 into computer - open your IDE (i used Thonny for this project) Flash the micropython firmware to the esp32
   1. Upload ESP32MicropytyhonLibraries ---> rename to ESP32Micro
   2. Upload boot.py and greenhouse.py to root directory

## Main Project Folder

[Project Directory](/Code/Open-Air_Violet_PlatformIO/)

## Source Files

[Reference Documentation](/docs/Reference_Docs/)

## OpenAir CO2 Visualizer

[CO2 Visualizer](/Code/OpenAir_CO2_Viz/)

## List of Materials

[List of Materials](/extras/List_of_Materials.csv)

<details>
<summary>
    <b>Further Reading</b>
</summary>

### Project Goals and To Do

Located below is an extensive check list of goals and to-do items for the project.

- [ ] Here is an example item.
- [x] Here is an example checked item.

</details>

[Top](#seedling-openair-violet-seedling)
