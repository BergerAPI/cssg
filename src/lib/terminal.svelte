<script>
  import { onMount } from "svelte";

  let output = [];

  // fake file system (very bad i know)
  let currentDir = "/";
  let folders = {
    "/": [
      {
        type: "file",
        name: "posts.page",
        contents: "/posts",
      },
      {
        type: "file",
        name: "home.page",
        contents: "/",
      },
      {
        type: "file",
        name: "hello.txt",
        contents:
          "Hello my friend. I'm glad, that you discovered the cat command!",
      },
      {
        type: "folder",
        name: "/secret",
      },
    ],
    "/secret": [
      {
        type: "file",
        name: ".credentials.txt",
        contents:
          "Did you really think, that you'd get my credentials? :kek: 😂",
      },
      {
        type: "folder",
        name: "/.test",
      },
    ],
    "/.test": [
      {
        type: "file",
        name: ".credentials2.txt",
        contents:
          "Did you really think, that you'd get my credentials? :kek: 😂",
      },
    ],
  };

  const commands = [
    {
      trigger: "echo",
      description: "Print things.",
      run: (args, print) => {
        print(args.join(" "));
      },
    },
    {
      trigger: "help",
      description: "Do you need help?",
      run: (_, print) => {
        print("Help for you:");
        print(" ");

        commands.forEach((item) => {
          print(item.trigger + " - " + item.description);
        });
      },
    },
    {
      trigger: "ls",
      description: "Lists every file and folder in your directory.",
      run: (args, print) => {
        let force = args.includes("-f");

        print("Files and Folders in " + currentDir + ":");

        folders[currentDir].forEach((item) => {
          if (
            (!item.name.startsWith(".") && !item.name.startsWith("/.")) ||
            force
          )
            print(" - " + item.name);
        });
      },
    },
    {
      trigger: "cd",
      description: "Change Directory.",
      run: (args, print) => {
        if (args.length <= 0) {
          push("Please specify the destination directory.", "red");
          return;
        }

        let destination = (args[0].startsWith("/") ? "" : "/") + args[0];
        let exists = folders[currentDir].find(
          (item) => item.type == "folder" && item.name == destination
        );

        if (destination === "/..") {
          let split = currentDir.split("/");
          currentDir = "/" + split[split.length - 2] || "/";
        } else {
          if (!folders[destination] || !exists) {
            print("No such folder.");
            return;
          }

          currentDir = destination;
        }

        print("You're now in " + currentDir);
      },
    },
    {
      trigger: "cat",
      description: "Print the contents of a file.",
      run: (args, print) => {
        if (args.length <= 0) {
          push("Please specify the file.", "red");
          return;
        }

        let file = args[0];
        let item = folders[currentDir].find(
          (item) => item.type == "file" && item.name == file
        );

        if (file.includes("/")) {
          let split = file.split("/");
          let sDir = currentDir;

          split.slice(0, -1).forEach((item) => (currentDir = "/" + item));

          item = folders[currentDir].find(
            (item) =>
              item.type == "file" && item.name == split[split.length - 1]
          );

          currentDir = sDir;
        }

        if (!item) {
          print("File doesn't exist.", "red");
          return;
        }

        print(item.contents);
      },
    },
    {
      trigger: "clear",
      description: "Removing every line.",
      run: (_, print) => {
        const oLength = output.length;

        output = [];

        print("Cleared " + oLength + " lines.");
      },
    },
    {
      trigger: "neofetch",
      description: "Infos about the system.",
      run: (_, print) => {
        print("                    'c.          niclas@macbook", "#06d6a0");
        print("                 ,xNMM.          --------------", "#06d6a0");
        print("               .OMMMMo           Name: Niclas", "#06d6a0");
        print("               OMMM0,            Country: Germany", "#06d6a0");
        print("     .;loddo:' loolloddol;.      Status: Student", "#06d6a0");
        print(
          "   cKMMMMMMMMMMNWMMMMMMMMMM0:    Experience: 5 years",
          "#06d6a0"
        );
        print(" .KMMMMMMMMMMMMMMMMMMMMMMMWd.    Web Dev 💪", "#ffd166");
        print(
          " XMMMMMMMMMMMMMMMMMMMMMMMX.      Software developer 🤯",
          "#ffd166"
        );
        print(";MMMMMMMMMMMMMMMMMMMMMMMM:       ", "#ef476f");
        print(".MMMMMMMMMMMMMMMMMMMMMMMMX.      ", "#ef476f");
        print(" kMMMMMMMMMMMMMMMMMMMMMMMMWd.    ", "#ef476f");
        print(" .XMMMMMMMMMMMMMMMMMMMMMMMMMMk   ", "#ef476f");
        print("  .XMMMMMMMMMMMMMMMMMMMMMMMMK.   ", "#ecbcfd");
        print("    kMMMMMMMMMMMMMMMMMMMMMMd     ", "#ecbcfd");
        print("     ;KMMMMMMMWXXWMMMMMMMk.      ", "#118ab2");
        print("       .cooc,.    .,coo:.        ", "#118ab2");

        push(" ");
      },
    },
  ];

  function push(text, color = "#FFF") {
    output = [...output, { text: text, color }];
  }

  function runCommand(input) {
    if (input.length === 0) return;

    const split = input.split(" ");

    const command = commands.find((item) => item.trigger === split[0]);

    const args = split.slice(1);

    if (!command) {
      push("The command '" + split[0] + "' wasn't found.", "red");

      return;
    }

    command.run(args, push);
  }

  onMount(() => {
    document.getElementById("input").focus();
    document.getElementById("form").onsubmit = (event) => {
      event.preventDefault();

      console.log(document.getElementById("input").value);

      runCommand(document.getElementById("input").value);
      document.getElementById("input").value = "";
    };

    runCommand("neofetch");
  });
</script>

<div class="content">
  <div class="header flex">
    <div class="header-buttons flex">
      <div class="header-button close" />
      <div class="header-button minimise" />
      <div class="header-button maximise" />
    </div>

    <div class="title">
      <p>Alacritty</p>
    </div>
  </div>

  <div class="body">
    <div id="output">
      {#each output as line}
        <pre id={line.text} style="color: {line.color}">{line.text}</pre>
      {/each}
    </div>

    <form id="form">
      <i class="fas fa-angle-right" />

      <input
        onblur="this.focus()"
        autoCorrect="off"
        autoCapitalize="none"
        autoComplete="off"
        id="input"
      />
    </form>
  </div>
</div>

<style>
  .content {
    width: 60vh;
    height: 60vh;

    max-width: 100%;

    margin-left: auto;
    margin-right: auto;

    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    position: absolute;
  }

  .flex {
    display: flex;
    align-items: center;
  }

  .header {
    background: rgb(40, 40, 40);
    border-radius: 0.8em 0.8em 0 0;
    position: relative;
    width: 100%;
  }

  .header-buttons {
    padding: 0.5em 1em;
  }

  .header-button {
    width: 0.75em;
    height: 0.75em;
    border-radius: 1em;
    margin-right: 0.5em;
  }

  .header-button.close {
    background: #ff4746;
  }

  .header-button.minimise {
    background: #ffbe00;
  }

  .header-button.maximise {
    background: #00db47;
  }

  .header .title {
    position: absolute;

    left: 50%;
    transform: translateX(-50%);
  }

  .header .title p {
    color: rgb(105, 105, 105);
    font-family: "Fira Code", monospace;
    font-size: 0.9em;
  }

  .body {
    height: 50vh;

    background-color: rgb(29 31 33);
    overflow: auto;
    border-radius: 0 0 0.8em 0.8em;

    display: flex;
    flex-direction: column;
    justify-content: flex-end;
  }

  .body #form {
    display: flex;
  }

  .body #input {
    background: transparent;
    border: none;
    color: white;
    font-size: 0.9em;
    font-family: "Fira Code", monospace;
    outline: none;
    width: 100%;
    margin-left: 0.5em;
  }
</style>
