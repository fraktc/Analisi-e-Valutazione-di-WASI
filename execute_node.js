'use strict';
const { readFile } = require('node:fs/promises');
const { WASI } = require('wasi');
const { argv, env } = require('node:process');

const wasi = new WASI({
  version: 'preview1',
  args: argv,
  env,
  preopens: {
    '/local': '.',
  },
});

// Get filename from command-line argument
const filename = argv[2];

if (!filename) {
  console.error('Usage: node your_script.js <filename>');
  process.exit(1);
}

(async () => {
  try {
    const wasm = await WebAssembly.compile(await readFile(filename));
    const instance = await WebAssembly.instantiate(wasm, wasi.getImportObject());

    wasi.start(instance); // Execute WASM without printing
  } catch (error) {
    console.error(`Error executing ${filename}:`, error);
  }
})();
