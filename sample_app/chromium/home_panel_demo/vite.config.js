import { defineConfig } from "vite";
import { nodePolyfills } from "vite-plugin-node-polyfills";

export default defineConfig({
  root: "./",
  build: {
    outDir: "dist",
  },
  publicDir: "public",
  plugins: [
    // By default, Vite does not automatically polyfill Node.js modules
    nodePolyfills(),
  ],
  define: {
    // By default, Vite doesn't include shims for NodeJS/
    // necessary for segment analytics lib to work
    global: "window",

    // Set the application version/
    // the package version is defined in the package.json
    __APP_VERSION__: JSON.stringify("1.00"),
  },
});
