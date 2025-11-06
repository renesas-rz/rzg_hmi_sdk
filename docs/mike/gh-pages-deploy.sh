#!/usr/bin/env bash

# mike/gh-pages-deploy.sh
# To deploy mike's webpage to GitHub gh-pages branch (for GitHub.io)

RED=$'\e[31m';
GREEN=$'\e[32m';
NC=$'\e[0m'; # No Color

mike() {
    echo -e "deploy and push to $1 $2"

    if [[ $2 == "" ]]; then
        mike deploy --push $1
    else
        mike deploy --push --update-aliases $1 $2
        mike set-default --push $2
    fi

    return;
}

get_tag() {
    while true; do
        read -p "Input target tag: " target_tag
        all_tags=($(git tag))
        exist=0
        for i in $(seq 1 ${#all_tags[@]}); do
            tag=${all_tags[i-1]}
            if [[ $tag == $target_tag ]]; then
                exist=1
            fi
        done

        if [[ $exist == 0 ]]; then
            echo -e "${RED}Tag not exist${NC}"
            echo -e "Existing tags: "
            for i in $(seq 1 ${#all_tags[@]}); do
                echo -e "${all_tags[i-1]}"
            done
        else
            break
        fi
    done

    read -p "Input target alias (enter for no alias): " target_alias

    if [[ $target_alias == "latest" && $target_tag != ${all_tags[${#all_tags[@]}-1]} ]]; then
        echo -e "${RED}You are trying to deploy non-latest tag as latest${NC}"

        echo -e "Latest tag is: ${GREEN}${all_tags[${#all_tags[@]}-1]}${NC}"
    fi

    tag_alias="$target_tag $target_alias"
    if [[ $target_alias == "" ]]; then
        tag_alias="$target_tag"
    fi

    while true; do
        read -p "Is it correct to push to ${GREEN}$tag_alias${NC}? " yn
        case $yn in
            [Yy]* ) mike $target_tag $target_alias; break;;
            [Nn]* ) get_tag; break;;
            * ) echo -e "Please answer yes or no.";;
        esac
    done

    return;
}

deploy_and_push() {
    git_tag=$(git describe --tags --abbrev=0)

    while true; do
        read -p "Is it correct to push to ${GREEN}$git_tag latest${NC}? " yn
        case $yn in
            [Yy]* ) mike $git_tag latest; break;;
            [Nn]* ) get_tag; break;;
            * ) echo -e "Please answer yes or no.";;
        esac
    done

    return;
}

main() {
    git_status=$(git status | tail -1)
    if [[ $git_status != "nothing to commit, working tree clean" ]]; then
        echo -e "${RED}Your workspace is not clean. Exit.${NC}"
    else
        deploy_and_push
    fi

    return;
}

while true; do
    read -p "Are you sure to ${RED}deploy${NC} and ${RED}push${NC} change of gh-pages to GitHub? " yn
    case $yn in
        [Yy]* ) main; break;;
        [Nn]* ) exit;;
        * ) echo -e "Please answer yes or no.";;
    esac
done
