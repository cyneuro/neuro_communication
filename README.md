# Communication in Brain Circuits and Systems

Communication in the brain occurs at multiple structural levels of increasing complexity. 
Here we provide examples of computational and statistical models which can be used to analyze communication properties at each level.

## Computational models

Used to model brain structures (cells, brain regions) using biophysical principles. 
Analyzing a properly tuned model can reveal fundamental biological principles of neural phenomena.

1. Single cell: a basic hardware unit for communication.
  - [Hodgkin-Huxley model](HH/hh_spiker.ipynb)

2. Generating neural oscillations.
  - [PING-Assembly network](PING-Assembly_BMTK/PING-Assembly_BMTK.ipynb)

## Statistical models and paradigms

Used to provide insights on the functional properties of brain structures using data-driven (statistical) approaches.

1. Neural activity recordings as a hardware indicator of communication
  - LFP (planned)
  - fMRI (planned)
  - [EEG](eeg_emotion_classification.ipynb)

2. Estimating functional connectivity during communication
  - [DCM](DCM/DCM_tutorial.ipynb)

## Communication hypotheses

Insights from computational and statistical models reveal potential mechanisms underlying communication.
Some of them are listed below.

1. Communication and coherence
  - Coh-th-Com vs Com-th-Coh: [SSM model (theory)](SSM/Vinck2021_SSM_tutorial.ipynb), [SSM model (tested on a PING network, one-way)](SSM/PING-Assembly-BMTK_Vinck/PING-Assembly_BMTK_OneWay.ipynb), [SSM model (tested on a PING network, two-way)](SSM/PING-Assembly-BMTK_Vinck/PING-Assembly_BMTK_TwoWay.ipynb)
2. Memory encoding and decoding
  - [Spatial computing model](SpatialComputing.ipynb)
