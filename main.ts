import { $ } from "bun";

await $`g++ main.cpp entities/*.cpp components/*.cpp -o main`;

const files = await $`ls input/*.txt`.text();

for (const file of files.split("\n")) {
  if (file) {
    await $`./main.exe ${file.replace(/\\/g, "/")}`;
  }
}
