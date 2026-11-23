# Modern C++ Algorithms Workshop

Today we’ll practise refactoring: improving the quality of code without changing its behaviour. Each exercise is based on a problem you’re likely to encounter in game code. Look for what each raw loop does, replace it with a C++ standard library operation that makes its intent clear, and run the existing tests to check that the behaviour hasn’t changed.

## Open in Visual Studio

You can work in [Compiler Explorer](#run-in-compiler-explorer) in your browser without installing anything, or you can work in Visual Studio on Windows. To use Visual Studio, first clone the workshop repository. Cloning makes a copy of the source code on your computer and keeps its Git history.

1. Clone [ulfben/algorithms-workshop](https://github.com/ulfben/algorithms-workshop) using one of these options. For GitHub Desktop or Visual Studio, use the address `https://github.com/ulfben/algorithms-workshop.git`.

   - **Git in PowerShell:** If Git is available in PowerShell, run these commands to clone the workshop into your Windows user folder.

     ```powershell
     cd $HOME
     git clone https://github.com/ulfben/algorithms-workshop.git
     ```

   - **GitHub Desktop:** Open [GitHub Desktop](https://desktop.github.com/) and choose **File → Clone repository → URL**. Paste the address, choose where to save the copy under **Local path**, and click **Clone**.

   - **Visual Studio:** On the start window, choose **Clone a repository**. If Visual Studio is already open, choose **Git → Clone Repository**. Paste the address into **Repository location**, choose where to save the copy under **Path**, and click **Clone**.

   Note where you saved the copy so you can find it in File Explorer. In Visual Studio, choose **File → Open → Folder** and open the folder containing `CMakeLists.txt`.
2. Use the `windows-x64-debug` preset and wait for CMake to finish configuring. The first configure downloads GoogleTest. Use the **Desktop development with C++** workload with CMake tools installed.
3. Select an exercise in the dropdown beside the green Run button. Press **Ctrl+F5** to build and run that exercise’s tests, or **F5** to debug them. Test Explorer’s **Run All** runs the whole workshop.
4. Edit the exercise’s `.cpp` in the `exercises` folder. Once it builds and its tests pass, open **Git Changes**, stage that exercise file, and enter a message that describes the change. Then choose **Commit Staged**.

## How to work

1. Start with **ex01 — Search a combat roster**. Run the tests before you change anything.
2. Read the scenario and the tests. Identify what the loop selects or changes, what it returns, and whether order matters.
3. Refactor one function at a time using the hint. Use the linked cppreference page to check the header, arguments and return value. Name lambda parameters for the things they represent, and capture the values the lambda needs.
4. Rerun the tests. If you have time, consider which inputs the tests cover and whether any edge cases are missing.

Each exercise is a standalone Google Test program with its own `main`.

## Run in Compiler Explorer

[Open exercise 1 in Compiler Explorer](https://compiler-explorer.com/z/hMWKnjehd).

Press **Ctrl+Enter** to compile and run the code. The Google Test output appears on the right.

To switch exercises, duplicate the browser tab and replace all the code with the contents of the next exercise’s `.cpp` file.

## AI use

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="assets/0rwx/AI-0-dark.svg">
  <img src="assets/0rwx/AI-0-light.svg" alt="AI:0" width="52" height="52">
</picture>
<picture>
  <source media="(prefers-color-scheme: dark)" srcset="assets/0rwx/AI-R-dark.svg">
  <img src="assets/0rwx/AI-R-light.svg" alt="AI:r" width="52" height="52">
</picture>

- **AI:0 for the exercise.** Read the loop and tests yourself, write every line of your refactor, and run and interpret the tests. That reading, refactoring, and checking is what you’re practising.
- **AI:r for help.** You can ask AI to explain a C++ concept or standard-library utility, or to help you understand an error or warning. Use the explanation to work out and verify your own change.

**Pro tip.** Compiler Explorer gives you a place to write the refactor without Visual Studio’s AI autocomplete.

The symbols come from the [0rwx framework](https://0rwx.com). [Original artwork](https://github.com/NamtaoProductions/0rwx.com/tree/main/static)

## Exercises

Start with the queries. Then choose exercises from the remaining groups. Some files contain sibling tasks that use the same game data to answer different questions.

| Exercise | What the code does | Practice |
| --- | --- | --- |
| [1. Search a combat roster](exercises/ex01_find_first_dead.cpp) | Check for an exact selected ID and find the first dead enemy in spawn order. | `find`, `find_if`, checking for `end()` |
| [2. Count poisoned enemies](exercises/ex02_count_poisoned.cpp) | Count active poison flags for a debug HUD. | `count_if` |
| [3. Inspect a map row](exercises/ex03_row_walkable.cpp) | Check if every tile is floor, any tile is lava, or no tile is a wall. | `all_of`, `any_of`, `none_of`, empty input |
| [4. Total inventory weight](exercises/ex04_total_weight.cpp) | Sum fractional item weights for the inventory UI. | `accumulate`, the initial value and its type |
| [5. Apply an area effect](exercises/ex05_apply_damage.cpp) | Change HP and keep it in the legal range. | `clamp` in a range-based loop |
| [6. Clean up bullets](exercises/ex06_remove_inactive_bullets.cpp) | Remove spent and off-screen bullets, keeping the order of the survivors. | `erase_if`, a predicate with captures |
| [7. Rank and select targets](exercises/ex07_rank_targets.cpp) | Rank all targets for the menu, or select the closest one for auto-lock. | `sort`, `min_element`, a shared ranking rule |
| [8. Group nearby enemies](exercises/ex08_partition_near.cpp) | Put nearby enemies first and return the boundary between the groups. | `partition`, an iterator that marks a boundary |
| [9. Collapse repeated collision reports](exercises/ex09_unique_contacts.cpp) | Keep the first sample in each consecutive run for a debug log. | `unique`, equivalence, erasing the unused tail |
| [10. Select enemies and make labels](exercises/ex10_filter_and_label_enemies.cpp) | Copy matching enemy records for the inspector and make names from an existing selection. | `copy_if` and `transform` in separate functions |
| [11. Shuffle a deck](exercises/ex11_shuffle_deck.cpp) | Shuffle cards with the random engine supplied by the game. | `shuffle`, testing that all cards survive |

## Try passing a view by value

Modern C++ often favours passing small objects by value. A `const&` parameter lets a function read an existing object without copying it. When the function only needs a sequence of elements or characters, you can pass a small **view** by value. The view says where the data starts and how many elements there are. The original data stays where it is and must stay alive while the view is in use.

- If the function takes a `const std::vector<T>&` and just reads the elements, try `std::span<const T>`. The caller can now pass a vector, an array, or a slice of either. Exercise 3 already uses this. [`std::span`](https://en.cppreference.com/cpp/container/span)
- If the function reads text through a `const std::string&` or a pointer and a length, try `std::string_view`. The caller can pass a string, a string literal, or part of a string. [`std::string_view`](https://en.cppreference.com/cpp/string/basic_string_view)

Once your algorithm refactor passes, try changing a parameter and run the same tests. Use `std::span<T>` if the function needs to change or reorder elements. Keep the vector reference in exercises 6 and 9, where the function changes the vector’s size.
