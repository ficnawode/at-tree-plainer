#include "ATTPConfigParser.hpp"
#include "AtTreePlainer.hpp"

#include "AnalysisTree/PlainTreeFiller.hpp"
#include "AnalysisTree/TaskManager.hpp"

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "Wrong number of arguments! Please use:\n  ./main "
                     "<path-to-json-config>\n";
        return EXIT_FAILURE;
    }
    const std::string& config_file_path = argv[1];
    auto config = ATTPConfig::Parser::Parse(config_file_path);
    ATTPConfig::Parser::Print(config);

    const bool make_plain_ttree{true};
    auto* man = AnalysisTree::TaskManager::GetInstance();
    man->SetOutputName("intermediate_tree.root", "pTree");

    auto* ml_plainer_task = new AtTreePlainer();
    ml_plainer_task->SetConfig(config);

    man->AddTask(ml_plainer_task);

    man->Init({config.input_filelist}, {"rTree"});
    man->Run(-1); // -1 = all events
    man->Finish();

    if(make_plain_ttree)
    {
        man->ClearTasks();
        std::ofstream filelist;
        filelist.open("filelist.txt");
        filelist << "intermediate_tree.root\n";
        filelist.close();

        auto* tree_task = new AnalysisTree::PlainTreeFiller();
        tree_task->SetInputBranchNames({config.output_branch_name});
        tree_task->SetOutputName(config.output_filename, "plain_tree");
        tree_task->AddBranch(config.output_branch_name);

        man->AddTask(tree_task);

        man->Init({"filelist.txt"}, {"pTree"});
        man->Run(-1); // -1 = all events
        man->Finish();
    }
    return EXIT_SUCCESS;
}
