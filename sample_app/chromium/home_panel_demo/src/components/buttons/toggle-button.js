import { LitElement, css, html } from "lit";

export class ToggleButton extends LitElement {
  // Define reactive properties
  static properties = {
    id: { type: String },
    // public properties
    // the custom web element's attributes
    checked: { type: Boolean, reflect: true },
    // internal states
    _active: { state: true },
  };

  constructor() {
    super();
    // set the default value for the element's attributes
    this.id = undefined;
    this.checked = false;

    // set the default internal states
    this._active = false;
  }

  render() {
    return html`
      <div class="container">
        <span class="text">OFF</span>
        <label class="switch">
          <input
            id=${this.id}
            type="checkbox"
            @click="${this._handleClick}"
            ?checked=${this.checked}
          />
          <span class="slider"></span>
        </label>
        <span class="text">ON</span>
      </div>
    `;
  }

  /**
   * handle input clicked
   * @param {Event} e click event
   */
  _handleClick(e) {
    this._active = !this._active;
    // register a custom button toggled event
    let myEvent = new CustomEvent("toggled", {
      detail: { active: this._active },
      bubbles: true,
      composed: true,
    });
    this.dispatchEvent(myEvent);
  }

  static styles = css`
    :host {
      display: block;
      color: white;
    }
    .container {
      box-sizing: border-box;
      display: flex;
      align-items: center;
      gap: 0.5em;
    }
    .switch {
      position: relative;
      display: inline-block;
      width: var(--toggle-button-width, 80px);
      height: var(--toggle-button-height, 40px);
    }
    .slider {
      position: absolute;
      top: 0;
      left: 0;
      right: 0;
      bottom: 0;
      background-color: var(--toggle-button-color, #ccc);
      transition: 0.4s;
      border-radius: 34px;
      cursor: pointer;
    }
    .switch input {
      display: none;
    }
    .slider::before {
      position: absolute;
      content: "";
      height: var(--toggle-button-thumb-size, 40px);
      width: var(--toggle-button-thumb-size, 40px);
      left: 0;
      bottom: 0;
      background-color: white;
      transition: 0.4s;
      border-radius: 50%;
    }
    input:checked + .slider {
      background-color: var(--toggle-button-checked-color, #80f342);
    }
    input:checked + .slider::before {
      transform: translateX(
        calc(
          var(--toggle-button-width, 80px) - var(--toggle-button-height, 40px)
        )
      );
    }
    .text {
      font-size: var(--toggle-button-font-size, 2rem);
    }
    @media screen and (max-width: 1900px) {
      .switch {
        width: var(--toggle-button-width, 60px);
        height: var(--toggle-button-height, 30px);
      }
      .slider::before {
        height: var(--toggle-button-thumb-size, 30px);
        width: var(--toggle-button-thumb-size, 30px);
      }
      input:checked + .slider::before {
        transform: translateX(
          calc(
            var(--toggle-button-width, 60px) - var(--toggle-button-height, 30px)
          )
        );
      }
      .text {
        font-size: var(--toggle-button-font-size, 1rem);
      }
    }
  `;
}

window.customElements.define("toggle-button", ToggleButton);
