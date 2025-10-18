# Advanced Computing Lab I (CS1051)

This repository contains the course materials for **Advanced Computing Lab I (CS1051)** at the National Institute of Technology Durgapur. The course focuses on practical applications of advanced computing concepts, including Advanced Algorithms, AI and Machine Learning, and Networking.

## How to Contribute?

To contribute to the repo [CS1051][def1], you should follow the standard GitHub contribution workflow. Here’s a step-by-step guide:

### 1. Fork the repository

- Go to your repo’s GitHub page.
- Click **Fork** (top-right corner).
- This creates a personal copy of the repo under the contributor’s GitHub account.

### 2. Clone the repo

```bash
git clone https://github.com/<YOUR-USERNAME>/CS1051.git
cd CS1051
```

### 3. Create a new branch

Always work on a new branch based on the features, not on `main`:

```bash
git checkout -b <YOUR-BRANCH-NAME>
```

Example:

```bash
git checkout -b add-tcp-udp-examples
```

### 4. Make changes

- Add or modify your code files (`sender.c`, `receiver.c`, `README.md`, etc.).
- Run and test the programs to ensure correctness.
- Stage changes:

  ```bash
  git add .
  ```

- Commit with a meaningful message:

  ```bash
  git commit -m <YOUR-COMMIT-MESSAGE>
  ```

  Example:

  ```bash
  git commit -m "Added UDP server/client example"
  ```

### 5. Push changes

```bash
git push origin <YOUR-BRANCH-NAME>
```

Example:

```bash
git push origin add-tcp-udp-examples
```

### 6. Open a Pull Request (PR)

- Go to your forked repo on GitHub.
- Click **Compare & pull request**.
- Provide a description (what you changed, why).
- Submit the PR.

The repo maintainer can then review and merge it.

### 7. Keeping your fork in sync

If the original repo ([`debarghamitraroy/CS1051`][def1]) changes, update your fork:

```bash
git remote add upstream https://github.com/debarghamitraroy/CS1051.git
git fetch upstream
git checkout main
git merge upstream/main
```

Then push:

```bash
git push origin main
```

## Steps to Create an Issue

If you find any issues (possibly bug) in the repo then create an issue by following the step by step procedure.

1. **Go to the repository**
   Open [CS1051](https://github.com/debarghamitraroy/CS1051).

2. **Navigate to the Issues tab**
   At the top (below the repo name), click on **Issues**.

3. **Click “New issue”**
   On the right side, click the green **New issue** button.

4. **Fill in the issue details**:

   - **Title:** A short summary of the problem/feature.

     Example: `Bug: receiver.c crashes if no arguments are provided`

   - **Description:** Explain clearly what the issue is.
     You can use Markdown for formatting.

   Example template:

   ```markdown
   ### Description

   The program crashes when `receiver.c` is run without command-line arguments.

   ### Steps to Reproduce

   1. Compile the program: `gcc receiver.c -o receiver`
   2. Run without args: `./receiver`
   3. Program crashes with segmentation fault.

   ### Expected Behavior

   It should print a usage message instead of crashing.

   ### Environment

   - OS: Ubuntu 24.04.2
   - Compiler: gcc 13.3.0
   ```

5. **Submit**
   Click **Submit new issue**. The issue will now appear in the repo’s Issues list.

[def1]: https://github.com/debarghamitraroy/CS1051
