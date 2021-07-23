<script>
  import { onMount } from "svelte";

  let output = [];

  const commands = [
    {
      trigger: "echo",
      run: (args, print) => {
        print(args.join(" "));
      },
    },
    {
      trigger: "clear",
      run: () => {
        output = [];
      },
    },
  ];

  function push(text) {
    output = [...output, { text, color: "#FFF" }];
  }

  function runCommand(input) {
    if (input.length === 0) return;

    const split = input.split(" ");

    const command = commands.find((item) => item.trigger === split[0]);

    const args = split.slice(1);

    if (!command) return;

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
        <p id={line.text} style="color: {line.color}">{line.text}</p>
      {/each}
    </div>

    <form id="form">
      <!-- svelte-ignore a11y-autofocus -->
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
    margin: 0 auto;
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

  .body .current {
    height: 20px;
    width: 100%;
  }

  .body #input {
    background: transparent;
    border: none;
    color: white;
    font-size: 0.9em;
    font-family: "Fira Code", monospace;
    outline: none;
    width: 100%;
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
