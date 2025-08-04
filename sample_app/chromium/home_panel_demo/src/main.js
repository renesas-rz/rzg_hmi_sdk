import { Router } from "@vaadin/router";

import { LitElement, css, html } from "lit";

// Initialize the router
const root = document.getElementById("root");
export const router = new Router(root);

// Define path to each page component
const routes = [
  {
    path: "/",
    component: "app-layout",
    action: async () => {
      await import("./components/sidebar/list-items");
      await import("./components/sidebar/sidebar");
    },
    children: [
      {
        path: "/",
        component: "dashboard-page",
        action: async () => {
          await import("./components/music-player/music-widget");
          await import("./components/widgets/widget-container");
          await import("./components/widgets/icon-widget");
          await import("./components/widgets/weather-widget");
          await import("./pages/dashboard");
        },
      },
      {
        path: "chart",
        component: "wheather-info-page",
        action: async () => {
          await import("./components/chart/temperature-chart");
          await import("./pages/weather-info");
        },
      },
      {
        path: "home-automation",
        component: "home-automation-page",
        action: async () => {
          await import("./components/buttons/toggle-button");
          await import("./components/slider/round-slider");
          await import("./components/slider/slider");
          await import("./components/widgets/widget-container");
          await import("./components/widgets/date-widget");
          await import("./components/widgets/aircon-widget");
          await import("./components/widgets/progress-widget");
          await import("./components/widgets/device-widget");
          await import("./components/widgets/graph-widget/graph-widget");
          await import("./pages/home-automation");
        },
      },
      {
        path: "camera",
        component: "live-camera-page",
        action: async () => {
          await import("./components/select-box/select-box");
          await import("./components/video-camera/video-camera");
          await import("./pages/live-camera");
        },
      },
      {
        path: "webgl-gallery",
        component: "gl-image-gallery-page",
        action: async () => {
          await import("./components/image-slider/gl-image-slider");
          await import("./pages/gl-image-gallery");
        },
      },
    ],
  },
];

const routesG2LC = [
  {
    path: "/",
    component: "app-layout",
    action: async () => {
      await import("./components/sidebar/list-items");
      await import("./components/sidebar/sidebar");
    },
    children: [
      {
        path: "/",
        component: "dashboard-page",
        action: async () => {
          await import("./components/music-player/music-widget");
          await import("./components/widgets/widget-container");
          await import("./components/widgets/icon-widget");
          await import("./components/widgets/weather-widget");
          await import("./pages/dashboard");
        },
      },
      {
        path: "chart",
        component: "wheather-info-page",
        action: async () => {
          await import("./components/chart/temperature-chart");
          await import("./pages/weather-info");
        },
      },
      {
        path: "home-automation",
        component: "home-automation-page",
        action: async () => {
          await import("./components/buttons/toggle-button");
          await import("./components/slider/round-slider");
          await import("./components/slider/slider");
          await import("./components/widgets/widget-container");
          await import("./components/widgets/date-widget");
          await import("./components/widgets/aircon-widget");
          await import("./components/widgets/progress-widget");
          await import("./components/widgets/device-widget");
          await import("./components/widgets/graph-widget/graph-widget");
          await import("./pages/home-automation");
        },
      },
      {
        path: "camera",
        component: "live-camera-page",
        action: async () => {
          await import("./components/select-box/select-box");
          await import("./components/video-camera/video-camera");
          await import("./pages/live-camera");
        },
      },
      {
        path: "image-gallery",
        component: "image-gallery-page",
        action: async () => {
          await import("./components/image-gallery/image-gallery");
          await import("./pages/images-gallery");
        },
      },
    ],
  },
];
// Configure the application routes
if (import.meta.env.VITE_RZG2LC !== "true") router.setRoutes(routes);
else router.setRoutes(routesG2LC);

// Define a layout component for the whole application
export class AppLayout extends LitElement {
  static get properties() {
    return {
      location: { type: Object },
    };
  }

  constructor() {
    super();
    // Vaadin Router updates `location` automatically
    // since this component is a route component for `/`
    this.location = router.location;
  }

  render() {
    return html`
      <header>
        <svg
          xmlns="http://www.w3.org/2000/svg"
          width="240"
          height="60"
          viewBox="-0.84017778 -0.84017778 177.38953556 29.68628156"
          class="logo"
        >
          <path
            d="M 54.457436,5.0449188 L 54.457436,22.611169 L 58.006186,22.611169 L 58.006186,9.3686688 C 58.163686,9.3686688 58.237436,9.4224188 58.369936,9.5686688 L 67.791186,20.631169 C 69.267436,22.419919 70.322436,22.611169 72.836186,22.611169 L 76.633686,22.611169 L 76.633686,5.0449188 L 73.094936,5.0399188 L 73.094936,18.194919 C 72.943686,18.194919 72.863686,18.144919 72.744936,17.996169 L 63.589936,7.2736688 C 62.161186,5.6236688 61.334936,5.0449188 57.639936,5.0449188 L 54.457436,5.0449188 z"
            style="fill-opacity: 1; fill-rule: nonzero; stroke: none;"
          />
          <path
            d="M 40.137316,7.5449188 L 49.067316,7.5599188 C 49.508566,7.5599188 49.818566,7.4149188 50.031066,7.0174188 L 51.088566,5.0449188 L 38.298566,5.0449188 C 32.634816,5.0449188 29.872316,7.1011688 29.872316,11.323669 L 29.872316,16.179919 C 29.872316,20.701169 32.709816,22.611169 38.304816,22.611169 L 49.403566,22.611169 C 49.818566,22.611169 50.131066,22.501169 50.344816,22.086169 L 51.374816,20.089919 L 40.126066,20.089919 C 37.178566,20.089919 36.117316,19.117419 36.117316,17.112419 L 36.117316,14.752419 L 47.794816,14.752419 C 48.233566,14.752419 48.539816,14.619919 48.758566,14.217419 L 49.811066,12.223669 L 36.117316,12.223669 L 36.117316,10.792419 C 36.117316,9.0874188 36.516066,7.5449188 40.137316,7.5449188"
            style="fill-opacity: 1; fill-rule: nonzero; stroke: none;"
          />
          <path
            d="M 90.869816,7.5449188 L 99.792316,7.5599188 C 100.23857,7.5599188 100.55982,7.4149188 100.77857,7.0174188 L 101.81607,5.0449188 L 89.031066,5.0449188 C 83.373566,5.0449188 80.588566,7.1011688 80.588566,11.323669 L 80.588566,16.179919 C 80.588566,20.701169 83.447316,22.611169 89.052316,22.611169 L 100.14357,22.611169 C 100.55982,22.611169 100.88357,22.501169 101.09857,22.086169 L 102.13607,20.089919 L 90.869816,20.089919 C 87.899816,20.089919 86.861066,19.117419 86.861066,17.112419 L 86.861066,14.752419 L 98.527316,14.752419 C 98.959816,14.752419 99.272316,14.619919 99.477316,14.217419 L 100.53732,12.223669 L 86.861066,12.223669 L 86.861066,10.792419 C 86.861066,9.0874188 87.226066,7.5449188 90.869816,7.5449188"
            style="fill-opacity: 1; fill-rule: nonzero; stroke: none;"
          />
          <path
            d="M 116.49844,16.661049 C 118.92094,17.454799 119.63469,17.796049 119.63469,18.723549 C 119.63469,19.517299 119.18344,20.103549 116.14094,20.103549 L 105.82469,20.089799 C 105.37969,20.089799 105.05594,20.222299 104.83844,20.631049 L 103.79469,22.611049 L 118.45594,22.611049 C 124.36969,22.611049 126.59094,20.748549 126.59094,18.198549 C 126.59094,16.709799 125.73844,14.752299 120.19219,12.921049 L 114.33719,11.011049 C 111.92594,10.213549 111.22094,9.8635488 111.22094,8.9560488 C 111.22094,8.2085488 111.62594,7.5447988 114.69969,7.5447988 L 123.42844,7.5597988 C 123.86719,7.5597988 124.16969,7.4160488 124.38469,7.0172988 L 125.44844,5.0472988 L 112.37219,5.0472988 C 106.47719,5.0472988 104.26094,6.8910488 104.26094,9.4560488 C 104.26094,10.948549 105.09094,12.927299 110.67344,14.752299 L 116.49844,16.661049 z"
            style="fill-opacity: 1; fill-rule: nonzero; stroke: none;"
          />
          <path
            d="M 169.33169,12.915919 L 163.47544,11.007169 C 161.08794,10.213419 160.34794,9.8609188 160.34794,8.9534188 C 160.34794,8.2159188 160.82169,7.5446688 163.82169,7.5446688 L 172.54794,7.5596688 C 172.98044,7.5596688 173.28669,7.4159188 173.51294,7.0159188 L 174.56794,5.0446688 L 161.53919,5.0446688 C 155.59169,5.0446688 153.42044,6.8859188 153.42044,9.4559188 C 153.42044,10.948419 154.25919,12.925919 159.77794,14.752169 L 165.63294,16.660919 C 168.04169,17.454669 168.78544,17.800919 168.78544,18.720919 C 168.78544,19.448419 168.30544,20.103419 165.26044,20.103419 L 153.39794,20.085919 L 144.19919,5.0446688 L 140.68669,5.0446688 C 137.96294,5.0446688 136.60044,5.8034188 135.32919,7.8671688 L 126.30669,22.610919 L 132.40794,22.610919 L 139.83669,9.4696688 C 140.02044,9.1496688 140.16794,9.1634188 140.31294,9.1634188 L 146.51919,20.085919 L 139.77919,20.085919 C 139.33794,20.085919 139.03544,20.218419 138.83419,20.630919 L 137.78669,22.610919 L 154.90044,22.610919 L 154.91794,22.610919 L 167.58794,22.610919 C 173.49919,22.610919 175.70919,20.744669 175.70919,18.194669 C 175.70919,16.709669 174.86294,14.749669 169.33169,12.915919"
            style="fill-opacity: 1; fill-rule: nonzero; stroke: none;"
          />
          <path
            d="M 1.2513157,21.775169 L 9.4488157,21.775169 L 9.4488157,13.561419 L 1.2513157,13.561419 L 1.2513157,21.775169 z"
            style="fill-opacity: 1; fill-rule: nonzero; stroke: none;"
          />
          <path
            d="M 0.99431573,3.2675488 C 0.69431573,3.4200488 0.22806573,3.7650488 0.15056573,4.1662988 C 0.15056573,4.1662988 0.0055657303,5.0187988 0.0055657303,5.0400488 C -0.04443427,5.3500488 0.25556573,5.2762988 0.38056573,5.1987988 C 1.6618157,4.4437988 3.0855657,3.7587988 4.3880657,3.3600488 C 10.519316,1.5075488 18.301816,1.4587988 19.659316,5.4650488 C 20.616816,8.2425488 16.723066,10.558799 14.528066,11.592549 C 13.680566,11.990049 13.396816,12.368799 13.339316,12.772549 C 13.291816,13.136299 13.416816,13.670049 13.905566,14.392549 C 16.984316,19.010049 26.135566,25.628799 35.114316,27.945049 C 35.488066,28.045049 35.671816,28.011299 35.824316,27.920049 C 35.908066,27.872549 36.013066,27.806299 35.851816,27.725049 C 29.888066,24.591299 24.191816,19.336299 21.343066,15.277549 C 20.691816,14.340049 20.524316,13.713799 20.566816,13.208799 C 20.608066,12.772549 21.010566,12.391299 21.868066,11.990049 C 25.053066,10.513799 28.300566,8.2650488 27.330566,4.5250488 C 25.916816,-0.85370118 10.694316,-1.6424512 0.99431573,3.2675488"
            style="fill-opacity: 1; fill-rule: nonzero; stroke: none;"
          />
        </svg>
      </header>
      <main>
        <slot></slot>
      </main>
      <sidebar-menu .location=${this.location.getUrl()}></sidebar-menu>
    `;
  }

  static styles = css`
    :host {
      margin: 0;
      padding: 0;
      display: grid;
      height: 100vh;
      grid-template-columns: 1fr auto;
      grid-template-rows: auto 1fr;
    }
    header {
      grid-column: 1;
      grid-row: 1;
      box-sizing: border-box;
      height: 80px;
      background-color: #e3e1ff;
      display: flex;
      justify-content: center;
      align-items: center;
      padding: 10px;
    }
    header svg.logo {
      transition: all 500ms ease-in-out;
      fill: #2f419a;
    }
    main {
      grid-column: 1;
      grid-row: 2;
    }
    sidebar-menu {
      grid-column: 2;
      grid-row: 1 / span 2;
    }

    @media screen and (max-width: 1023px) {
      header {
        height: 60px;
      }
      header svg.logo {
        width: 280px;
        height: 40px;
      }
    }
  `;
}

window.customElements.define("app-layout", AppLayout);
