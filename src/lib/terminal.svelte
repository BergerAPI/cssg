<script>
  import { onMount } from "svelte";

  let output = [];

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
      <p>Alacritty - BergerAPI</p>
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
    font-size: 0.9em;
    font-family: "Fira Code", monospace;
  }

  .body {
    height: 50vh;

    background-color: rgb(29 31 33);
    overflow: hidden;
    border-radius: 0 0 0.8em 0.8em;

    display: flex;
    flex-direction: column;
    justify-content: flex-end;
  }

  .body p {
    font-family: "Fira Code", monospace;
    font-size: 0.9em;
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

  @keyframes blink-caret {
    from,
    to {
      border-color: transparent;
    }
    50% {
      border-color: var(--color);
    }
  }
</style>
