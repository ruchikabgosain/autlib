# How to contribute to autlib

Thanks for your interest in contributing to `autlib`.

## Report bugs

- Describe what you expected to happen and what actually happened.
- If possible, include an [MCVE](https://stackoverflow.com/help/minimal-reproducible-example) to help us identify the issue.
- Provide information about the environment the bug occured on.
- Submit your issue using the provided template
- If possible, check if this issue is already solved in the repository

## Propose features

- Tell us what you would like to see included in `autlib`
- Submit your proposal using the provided template

## Submit patches

- Have a look at the [issues page](https://github.com/gkarlos/autlib/issues) to identify issues that you can solve or head over to the [TODO](./TODO) file to for a list of things we would like to add to `autlib`.
- Always include tests and clearly describe what your patch addresses and how.
- Make sure your patch addresses an <b>open</b> issue. If such an open issue doesn't exist make sure you create one first before PR.
- Include a string such us "Fixes #12345" in your commit message, where "12345" is the issue you fixed. 
- When your are set make a Pull Request (See [Creating a pull request](https://help.github.com/en/articles/creating-a-pull-request))

#### First time setup
- Download and install [git](https://git-scm.com/downloads)
- Configure your [username](https://help.github.com/en/articles/setting-your-username-in-git) and [email](https://help.github.com/en/articles/setting-your-commit-email-address-in-git):
  ```
  git config --global user.name 'your_name_here'
  git config --global user.email 'your_email_here'
  ```
- Make sure you have signed up for a [Github account](https://github.com/).

- Fork the `autlib` repository into your Github account by clicking the [Fork](https://github.com/gkarlos/autlib/fork) button.

- [Clone](https://help.github.com/en/articles/fork-a-repo#step-2-create-a-local-clone-of-your-fork) your fork locally:
    ```
    git clone https://github.com/{username}/autlib
    cd autlib
    ```
- Add the `autlib` repository as a remote:
    ```
    git remote add autlib-main https://github.com/gkarlos/autlib
    git fetch autlib-main
    ```

#### Start Coding
- Make sure you have read how to build `autlib` and have all requirements installed
- Create a new branch under which you will be working on. Branch off of the `-master` branch:
    ```
    git checkout -b your-branch-name origin/master
    ```
- Use your favorite editor (vim? :pizza:), make changes and [commit as you go](https://dont-be-afraid-to-commit.readthedocs.io/en/latest/git/commandlinegit.html#commit-your-changes).
- Make sure you include tests. Put those on their own file(s),under the [test](./test) directory. Feel free to add a subdirectory if needed. 
- Update [test/CMakeLists.txt](./test/CMakeLists.txt), adding your tests.
- Push your commits:
    ```
    git push --set-upstream origin your-branch-name
    ```
- Finally, [create a pull request](https://help.github.com/en/articles/creating-a-pull-request)
