# Communication in Brain Circuits and Systems

Communication in the brain occurs at multiple structural levels of increasing complexity. 
Here we provide examples of computational and statistical models which can be used to analyze communication properties at each level.

## Computational models

Used to model brain structures (cells, brain regions) using biophysical principles. 
Analyzing a properly tuned model can reveal fundamental biological principles of neural phenomena.

1. Single cell: a basic hardware unit for communication.
  - [Hodgkin-Huxley model](HH/hh_spiker.ipynb)
  - [Our tutorials on single cell properties](https://cyneuro.github.io/cyneuro-resources/training/comp_neuro_tutorials.html#content-training-comp-neuro-tutorials)

2. Generating neural oscillations.
  - [PING-Assembly network](PING-Assembly_BMTK/PING-Assembly_BMTK.ipynb)
  - [Facilitative, PING, EIO, M1 networks](https://github.com/cyneuro/Neural-Modeling-Manual/tree/main/Chapter-6-Full-Network-Models)

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

1. Coh-th-Com vs Com-th-Coh
  - [SSM model (theory)](SSM/Vinck2021_SSM_tutorial.ipynb)
  - [SSM model (tested on a PING network, one-way)](SSM/PING-Assembly-BMTK_Vinck/PING-Assembly_BMTK_OneWay.ipynb)
  - [SSM model (tested on a PING network, two-way)](SSM/PING-Assembly-BMTK_Vinck/PING-Assembly_BMTK_TwoWay.ipynb)
2. Memory encoding and decoding
  - [Spatial computing model (theory)](SpatialComputing.ipynb)

## Other packages
The following packages can be used for computational modeling:
- [NEURON](https://www.neuron.yale.edu/neuron/) (also see [MIT NEURON tutorial](https://web.mit.edu/neuron_v7.4/nrntuthtml/index.html))
- [BMTK](https://alleninstitute.github.io/bmtk/)
- [NEST](https://nest-simulator.readthedocs.io/en/stable/)
- [BRIAN](https://briansimulator.org)

## References

See [this file](references.bib) for references and bibliography.
