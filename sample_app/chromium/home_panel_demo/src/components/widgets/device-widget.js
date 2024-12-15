import { LitElement, css, html } from "lit";

export class DeviceWidget extends LitElement {
  // Define reactive properties
  static properties = {
    // public properties
    // the custom web element's attributes
    id: { type: String },
    title: { type: String },
    // internal states
    _active: { state: true },
  };

  constructor() {
    super();
    // set the default value for the element's attributes
    this.id = undefined;
    this.title = "title";
    this.href = "/";
    // set the default internal states
    this._active = false;
  }

  render() {
    return html`
      <widget-container>
        <span class="widget-title">${this.title}</span>
        ${this._active
          ? html` <slot name="active"></slot> `
          : html` <slot name="inactive"></slot> `}
        <toggle-button
          id=${this.id}
          @toggled=${(e) => {
            this._active = e.detail.active;
          }}
        ></toggle-button>
      </widget-container>
    `;
  }

  static styles = css`
    :host {
      display: block;
    }
    toggle-button {
      --toggle-button-width: 60px;
      --toggle-button-height: 30px;
      --toggle-button-thumb-size: 30px;
      --toggle-button-font-size: 1.7rem;
    }
    .widget-title {
      color: #ddd;
      font-size: 1.5rem;
    }
    @media screen and (max-width: 1900px) {
      toggle-button {
        --toggle-button-width: 40px;
        --toggle-button-height: 20px;
        --toggle-button-thumb-size: 20px;
        --toggle-button-font-size: 1rem;
      }
      .widget-title {
        font-size: 1rem;
      }
    }
  `;
}

window.customElements.define("device-widget", DeviceWidget);
