import { defineConfig, loadEnv } from "vite";
import { nodePolyfills } from "vite-plugin-node-polyfills";

export default ({ mode }) => {
  process.env = {
    ...process.env,
    ...loadEnv(mode, process.cwd()),
  };

  const env = loadEnv(mode, process.cwd());

  var version;

  if (env.VITE_MACHINE == "rzg2l" || env.VITE_MACHINE == "rzg2lc" || env.VITE_MACHINE == "rzg3l") {
    version = "2.01";
  } else {
    version = "2.00";
  }
  return defineConfig({
    root: "./",
    build: {
      outDir: "dist",
    },
    publicDir: "public",
    plugins: [
      // By default, Vite does not automatically polyfill Node.js modules
      nodePolyfills()
    ],
    define: {
      // By default, Vite doesn't include shims for NodeJS/
      // necessary for segment analytics lib to work
      global: "window",

      // Set the application version/
      // the package version is defined in the package.json
      __APP_VERSION__: JSON.stringify(version),
    },
  });
};
