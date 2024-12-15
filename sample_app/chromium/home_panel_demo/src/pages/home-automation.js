import { LitElement, css, html } from "lit";

/**
 * Class to create Home Automation page element
 */
export class HomeAutomationPage extends LitElement {
  constructor() {
    super();
  }

  render() {
    return html`
      <div class="container">
        <progress-widget
          class="temperature-widget"
          title="Room Temperature"
          value="25"
          unit="°C"
          max="50"
          style="
            --widget-progress-bar-color:#2f419a;
            "
        >
        </progress-widget>
        <progress-widget
          class="power-widget"
          title="Power Consumption"
          value="700"
          unit="kWh"
          max="1000"
          duration="30"
          style="
            --widget-progress-bar-color:#e03131;
            "
        >
        </progress-widget>
        <device-widget
          id="light-widget-1"
          class="light-widget-1"
          title="Light 1"
        >
          <svg
            xmlns="http://www.w3.org/2000/svg"
            height="56px"
            viewBox="0 -960 960 960"
            width="56px"
            fill="#ffd43b"
            class="shadow"
            slot="active"
          >
            <path
              d="M480-80q-33 0-56.5-23.5T400-160h160q0 33-23.5 56.5T480-80ZM320-200v-80h320v80H320Zm10-120q-69-41-109.5-110T180-580q0-125 87.5-212.5T480-880q125 0 212.5 87.5T780-580q0 81-40.5 150T630-320H330Zm24-80h252q45-32 69.5-79T700-580q0-92-64-156t-156-64q-92 0-156 64t-64 156q0 54 24.5 101t69.5 79Zm126 0Z"
            />
          </svg>
          <svg
            xmlns="http://www.w3.org/2000/svg"
            height="56px"
            viewBox="0 -960 960 960"
            width="56px"
            fill="#f9f8ff"
            slot="inactive"
          >
            <path
              d="M480-80q-33 0-56.5-23.5T400-160h160q0 33-23.5 56.5T480-80Zm0-720q-44 0-81.5 15.5T332-742l-58-56q41-38 93.5-60T480-880q125 0 212.5 87.5T780-580q0 71-25 121.5T698-376l-56-56q21-23 39.5-59t18.5-89q0-92-64-156t-156-64Zm368 688-57 57-265-265H330q-69-41-109.5-110T180-580q0-20 2.5-39t7.5-37L56-792l56-56 736 736ZM354-400h92L260-586v6q0 54 24.5 101t69.5 79Zm-6-98Zm134-94Zm164 312v80H320v-80h326Z"
            />
          </svg>
        </device-widget>
        <device-widget
          id="light-widget-2"
          class="light-widget-2"
          title="Light 2"
        >
          <svg
            xmlns="http://www.w3.org/2000/svg"
            height="56px"
            viewBox="0 -960 960 960"
            width="56px"
            fill="#ffd43b"
            class="shadow"
            slot="active"
          >
            <path
              d="M480-80q-33 0-56.5-23.5T400-160h160q0 33-23.5 56.5T480-80ZM320-200v-80h320v80H320Zm10-120q-69-41-109.5-110T180-580q0-125 87.5-212.5T480-880q125 0 212.5 87.5T780-580q0 81-40.5 150T630-320H330Zm24-80h252q45-32 69.5-79T700-580q0-92-64-156t-156-64q-92 0-156 64t-64 156q0 54 24.5 101t69.5 79Zm126 0Z"
            />
          </svg>
          <svg
            xmlns="http://www.w3.org/2000/svg"
            height="56px"
            viewBox="0 -960 960 960"
            width="56px"
            fill="#f9f8ff"
            slot="inactive"
          >
            <path
              d="M480-80q-33 0-56.5-23.5T400-160h160q0 33-23.5 56.5T480-80Zm0-720q-44 0-81.5 15.5T332-742l-58-56q41-38 93.5-60T480-880q125 0 212.5 87.5T780-580q0 71-25 121.5T698-376l-56-56q21-23 39.5-59t18.5-89q0-92-64-156t-156-64Zm368 688-57 57-265-265H330q-69-41-109.5-110T180-580q0-20 2.5-39t7.5-37L56-792l56-56 736 736ZM354-400h92L260-586v6q0 54 24.5 101t69.5 79Zm-6-98Zm134-94Zm164 312v80H320v-80h326Z"
            />
          </svg>
        </device-widget>
        <device-widget id="tv-widget" class="tv-widget" title="TV">
          <svg
            xmlns="http://www.w3.org/2000/svg"
            height="56px"
            viewBox="0 -960 960 960"
            width="56px"
            fill="#ffd43b"
            class="shadow"
            slot="active"
          >
            <path
              d="M320-120v-80h80v-80H160q-33 0-56.5-23.5T80-360v-400q0-33 23.5-56.5T160-840h640q33 0 56.5 23.5T880-760v400q0 33-23.5 56.5T800-280H560v80h80v80H320ZM160-360h640v-400H160v400Zm0 0v-400 400Z"
            />
          </svg>
          <svg
            xmlns="http://www.w3.org/2000/svg"
            height="56px"
            viewBox="0 -960 960 960"
            width="56px"
            fill="#f9f8ff"
            slot="inactive"
          >
            <path
              d="m853-221-53-53v-486H314l-80-80h566q33 0 56.5 23.5T880-760v480q0 18-6.5 32.5T853-221ZM127-833l73 73h-40v480h406L28-820l56-56L876-84l-56 56-172-172h-8v80H320v-80H160q-33 0-56.5-23.5T80-280v-480q0-37 23.5-55l23.5-18Zm237 351Zm195-33Z"
            />
          </svg>
        </device-widget>
        <device-widget id="wifi-widget" class="wifi-widget" title="WiFi">
          <svg
            xmlns="http://www.w3.org/2000/svg"
            height="56px"
            viewBox="0 -960 960 960"
            width="56px"
            fill="#ffd43b"
            class="shadow"
            slot="active"
          >
            <path
              d="M480-120q-42 0-71-29t-29-71q0-42 29-71t71-29q42 0 71 29t29 71q0 42-29 71t-71 29ZM254-346l-84-86q59-59 138.5-93.5T480-560q92 0 171.5 35T790-430l-84 84q-44-44-102-69t-124-25q-66 0-124 25t-102 69ZM84-516 0-600q92-94 215-147t265-53q142 0 265 53t215 147l-84 84q-77-77-178.5-120.5T480-680q-116 0-217.5 43.5T84-516Z"
            />
          </svg>
          <svg
            xmlns="http://www.w3.org/2000/svg"
            height="56px"
            viewBox="0 -960 960 960"
            width="56px"
            fill="#f9f8ff"
            slot="inactive"
          >
            <path
              d="M790-56 414-434q-47 11-87.5 33T254-346l-84-86q32-32 69-56t79-42l-90-90q-41 21-76.5 46.5T84-516L0-602q32-32 66.5-57.5T140-708l-84-84 56-56 736 736-58 56Zm-310-64q-42 0-71-29.5T380-220q0-42 29-71t71-29q42 0 71 29t29 71q0 41-29 70.5T480-120Zm236-238-29-29-29-29-144-144q81 8 151.5 41T790-432l-74 74Zm160-158q-77-77-178.5-120.5T480-680q-21 0-40.5 1.5T400-674L298-776q44-12 89.5-18t92.5-6q142 0 265 53t215 145l-84 86Z"
            />
          </svg>
        </device-widget>
        <aircon-widget class="aircon-widget"></aircon-widget>
        <graph-widget class="graph-widget"></graph-widget>
      </div>
    `;
  }

  static styles = css`
    :host {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100%;
    }
    svg {
      width: 86px;
      height: 86px;
    }
    .container {
      box-sizing: border-box;
      display: grid;
      grid-template-columns: repeat(3, 1fr) 520px;
      grid-template-rows: repeat(2, 1fr) 30%;
      gap: 16px;
      height: 85%;
      padding: 10px;
      transition: all 500ms ease;
    }
    .shadow {
      filter: drop-shadow(0px 0px 3px rgba(255, 212, 59, 1));
    }
    .aircon-widget {
      grid-column: 4;
      grid-row: 1 / span 3;
    }
    .light-widget-1 {
      grid-column: 2;
      grid-row: 1;
    }
    .light-widget-2 {
      grid-column: 3;
      grid-row: 1;
    }
    .wifi-widget {
      grid-column: 2;
      grid-row: 2;
    }
    .tv-widget {
      grid-column: 3;
      grid-row: 2;
    }
    .temperature-widget {
      grid-column: 1;
      grid-row: 1;
    }
    .power-widget {
      grid-column: 1;
      grid-row: 2;
    }

    .graph-widget {
      grid-column: 1 / span 3;
      grid-row: 3;
    }
    @media screen and (max-height: 800px) {
      .container {
        height: 90%;
      }
    }
    @media screen and (max-width: 1900px) {
      svg {
        width: 56px;
        height: 56px;
      }
      .container {
        grid-template-columns: repeat(3, 1fr) 400px;
      }
    }
  `;
}

window.customElements.define("home-automation-page", HomeAutomationPage);
