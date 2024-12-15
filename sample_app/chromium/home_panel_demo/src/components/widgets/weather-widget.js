import { LitElement, css, html } from "lit";

export class WeatherWidget extends LitElement {
  // Define reactive properties
  static properties = {
    // public properties
    // the custom web element's attributes
    href: { type: String },
  };

  constructor() {
    super();
    // set the default value for the element's attributes
    this.href = "/";
  }

  render() {
    return html`
      <a href=${this.href}>
        <div class="container">
          <slot></slot>
          <div class="info">
            <div class="location">
              <svg
                xmlns="http://www.w3.org/2000/svg"
                viewBox="0 -960 960 960"
                fill="#5961c0"
                class="location-icon"
              >
                <path
                  d="M480-480q33 0 56.5-23.5T560-560q0-33-23.5-56.5T480-640q-33 0-56.5 23.5T400-560q0 33 23.5 56.5T480-480Zm0 294q122-112 181-203.5T720-552q0-109-69.5-178.5T480-800q-101 0-170.5 69.5T240-552q0 71 59 162.5T480-186Zm0 106Q319-217 239.5-334.5T160-552q0-150 96.5-239T480-880q127 0 223.5 89T800-552q0 100-79.5 217.5T480-80Zm0-480Z"
                />
              </svg>
              <span class="location-text">Osaka</span>
            </div>
            <span class="location-temp">28°C</span>
            <span class="location-desc">Outdoor Temperature</span>
          </div>
        </div>
      </a>
    `;
  }

  static styles = css`
    :host {
      display: block;
    }
    a {
      text-decoration: none;
    }
    .container {
      box-sizing: border-box;
      background: var(--widget-background-color, #e9ecef);
      border-radius: 10px;
      width: 100%;
      height: 100%;
      display: flex;
      justify-content: space-between;
      align-items: center;
      flex-direction: row;
      padding: var(--widget-padding, 2rem 2.5rem);
      transition: all 300ms ease;
    }
    .container:hover {
      background: var(--widget-hover-background-color, #dbdbdb);
    }
    .info {
      text-align: right;
    }
    .location {
      display: flex;
      justify-content: flex-end;
      align-items: center;
      gap: 0.5rem;
    }
    .location svg {
      width: 56px;
      height: 56px;
    }
    .location-text,
    .location-temp,
    .location-desc {
      color: #5961c0;
      font-weight: bold;
      display: block;
      line-height: 1.2;
    }
    .location-text {
      font-size: 3.5rem;
    }
    .location-temp {
      font-size: 6rem;
    }
    .location-desc {
      font-size: 1.5rem;
    }
    @media screen and (max-height: 800px) {
      .container {
        padding: var(--widget-padding, 1.5rem 2rem);
      }
      .location svg {
        width: 32px;
        height: 32px;
      }
      .location-text,
      .location-temp,
      .location-desc {
        line-height: 1.5;
      }
      .location-text {
        font-size: 2rem;
      }
      .location-temp {
        font-size: 3rem;
      }
      .location-desc {
        font-size: 0.9rem;
      }
    }
  `;
}

window.customElements.define("weather-widget", WeatherWidget);
