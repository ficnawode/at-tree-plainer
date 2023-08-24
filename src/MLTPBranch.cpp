#include "MLTPBranch.hpp"
#include <array>

namespace MLTP
{
    Branch::Branch(MLTPConfig::Branch branch_config, AnalysisTree::Configuration *atree_config, AnalysisTree::BranchConfig &out_branch_config) : in_branch_name{Branch::ValidateBranch(branch_config.name, atree_config)},
                                                                                                                                                 out_branch_config_{out_branch_config}

    {
        for (auto &v : branch_config.vars)
        {
            vars_.push_back(Variable(v));
        }
    }

    void Branch::AddFields()
    {
        for (auto &v : vars_)
        {
            v.AddField(out_branch_config_);
        }
    }

    void Branch::SetFields(AnalysisTree::Container &out_particle, AnalysisTree::Container &in_particle)
    {
        for (auto &v : vars_)
        {
            v.SetField(out_particle, in_particle);
        }
    }

    void Branch::InitInIndices()
    {
        for (auto &v : vars_)
        {
            v.InitInId(in_branch_config_);
        }
    }

    void Branch::InitOutIndices()
    {
        for (auto &v : vars_)
        {
            v.InitOutId(out_branch_config_);
        }
    }

    bool Branch::IsInBranchNameValid(std::string in_branch_name)
    {
        static constexpr std::array valid_branch_names = {"RecEventHeader", "TofHits", "SimParticles", "VtxTracks", "TrdTracks"};

        return (std::find(std::begin(valid_branch_names), std::end(valid_branch_names), in_branch_name) != std::end(valid_branch_names));
    }
    AnalysisTree::Configuration &Branch::ValidateBranch(std::string in_branch_name, AnalysisTree::Configuration *config)
    {
        assert(Branch::IsInBranchNameValid(in_branch_name));
        return atree_config->GetBranchConfig(in_branch_name);
    }
}