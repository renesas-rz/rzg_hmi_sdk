import { LitElement, css, html } from "lit";
import { classMap } from "lit/directives/class-map.js";

import items from "./items";

export class Sidebar extends LitElement {
  // Define reactive properties
  static properties = {
    // public properties
    // the custom web element's attributes
    close: { type: Boolean },
    rotate: { type: Boolean },
    location: { type: Object },
  };

  constructor() {
    super();
    // set the default value for the element's attributes
    this.close = true;
    this.rotate = false;
    this.location = null;
  }

  /**
   * Toggle the sidebar
   */
  toggleSidebar() {
    this.close = !this.close;
    this.rotate = !this.rotate;
  }

  render() {
    // apply classes dynamically
    const navClasses = {
      // apply "close" class when the given property is set to true
      close: this.close,
    };
    const toggleBtnClasses = {
      // apply "rotate" class when the given property is set to true
      rotate: this.rotate,
    };

    return html`
      <div class="container">
        <button
          class="toggle-btn ${classMap(toggleBtnClasses)}"
          @click=${this.toggleSidebar}
        >
          <svg
            xmlns="http://www.w3.org/2000/svg"
            height="36px"
            viewBox="0 -960 960 960"
            width="36px"
            fill="#5f6368"
          >
            <path
              d="M440-240 200-480l240-240 56 56-183 184 183 184-56 56Zm264 0L464-480l240-240 56 56-183 184 183 184-56 56Z"
            />
          </svg>
        </button>
        <nav id="sidebar" class=${classMap(navClasses)}>
          <ul>
            <list-items .items=${items} .location=${this.location}></list-items>
          </ul>
          <div class="version">
            <span>Ver.${__APP_VERSION__}</span>
          </div>
        </nav>
      </div>
    `;
  }

  static styles = css`
    nav {
      box-sizing: border-box;
      height: 100vh;
      width: 320px;
      padding: 80px 5px 5px 5px;
      background-color: #2f419a;
      position: sticky;
      top: 0;
      align-self: flex-end;
      transition: 500ms ease-in-out;
      overflow: hidden;
      display: flex;
      flex-direction: column;
      justify-content: space-between;
    }
    ul {
      padding: 0;
      list-style-type: none;
    }
    .container {
      position: relative;
    }
    .header {
      display: flex;
      justify-content: flex-start;
      gap: 0.5em;
      margin-bottom: 16px;
    }
    .version {
      box-sizing: border-box;
      width: 310px;
      color: #fff;
      padding: 0.5rem;
    }
    .version span {
      display: block;
      text-align: right;
    }
    .close {
      width: 58px;
    }
    .toggle-btn {
      box-sizing: border-box;
      position: absolute;
      top: 16px;
      left: -25px;
      z-index: 2;
      padding: 5px;
      border: 3px solid #e3e1ff;
      border-radius: 50%;
      background-color: #8f92f6;
      display: flex;
      align-items: center;
      justify-content: center;
      cursor: pointer;
      transition: all 300ms ease;
    }
    .toggle-btn svg {
      transition: rotate 500ms ease-in-out;
      fill: #e6e6ef;
    }
    .toggle-btn:hover {
      background-color: #000755;
    }
    .rotate svg:last-child {
      rotate: 180deg;
    }

    @media screen and (max-width: 1900px) {
      nav {
        width: 280px;
      }
      .close {
        width: 60px;
      }
      .toggle-btn {
        top: 10px;
      }
      .toggle-btn svg {
        width: 24px;
        height: 24px;
      }
      .version {
        width: 270px;
      }
    }
  `;
}

window.customElements.define("sidebar-menu", Sidebar);
