import { $ } from "bun";

const files = await $`ls input/*.txt`.text();

for (const file of files.split("\n")) {
  if (file) {
    await $`./main.exe ${file.replace(/\\/g, "/")}`;
  }
}
