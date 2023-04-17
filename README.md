# ml_tree_plainer

## General information

ml_tree_plainer program is developed for conversion of complex AnalysisTree structure into plain tree (either AnalysisTree or ROOT::TTree).
It is based on at_tree_plainer by Oleksii Lubynets.

## Pre-requirements

### Root

ROOT6 is needed for installation:

https://root.cern/install/build_from_source/

Follow instructions
    
### AnalysisTree

https://github.com/HeavyIonAnalysis/AnalysisTree

Follow instructions

## Installation

Clone at_tree_plainer

    git clone git@git.cbm.gsi.de:o.lubynets/at_tree_plainer.git
    
Source ROOT

    source /path-to-root/install/bin/thisroot.sh
    
Export AnalysisTree libraries

    export AnalysisTree_DIR=/path-to-analysistree/install/lib/cmake/AnalysisTree
    
Install at_tree_plainer
    
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=/path-to-install-at_tree_plainer /path-to-source-at_tree_plainer
    make -j install
    
## First run

./main file_list.txt
where file_list.txt should contain names of PFSimple output AnalysisTree files

## Configuration

If one wants to add conersion of another fields then one should modify ATreePlainer class in several places:
 - add field ids as class members in .hpp
 - ad corresponding fields in ATreePlainer::Init()
 - initialize field ids in ATreePlainer::InitIndices()
 - perform copyng the field contentin ATreePlainer::Exec()

