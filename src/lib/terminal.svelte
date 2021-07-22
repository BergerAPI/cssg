<script>
  $: output = [];
  let currentLine = "";

  const invalid = [16, 91, 18, 9, 20, 38, 37, 39, 40];

  function push(text) {
    output.push({ text, color: "#FFF" });
  }

  function runCommand(input) {
    push(input);
  }

  function handleKeydown(event) {
    if (invalid.includes(event.keyCode)) return;

    if (event.key === "Backspace") {
      currentLine = currentLine.slice(0, -1);
    } else if (event.key == "Enter") {
      runCommand(currentLine);
      document.getElementById("output").innerHTML = output
        .map(
          ({ text, color }) =>
            '<p style="color: ' + color + '">' + text + "</p>"
        )
        .join("");
      currentLine = "";
    } else {
      currentLine += event.key;
    }
  }
</script>

<svelte:window on:keydown={handleKeydown} />

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
        <p style="color: {line.color}">{line.text}</p>
      {/each}
    </div>

    <p id="currentLine">{currentLine}</p>
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

    padding-bottom: 0.75em;
  }

  .body p {
    font-family: "Fira Code", monospace;
    font-size: 0.8em;
  }

  .body #currentLine {
    background-color: green;
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
