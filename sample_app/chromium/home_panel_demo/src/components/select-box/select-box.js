import { LitElement, css, html } from "lit";

export class SelectBox extends LitElement {
  // Define reactive properties
  static properties = {
    // public properties
    // the custom web element's attributes
    items: { type: Array },
  };

  constructor() {
    super();
    // set the default value for the element's attributes
    this.items = null;
  }

  // query the details element in the internal DOM using getter pattern
  get _details() {
    return this.renderRoot.querySelector(".custom-select");
  }

  render() {
    return html`
      <details class="custom-select">
        <summary class="radios">
          <input
            type="radio"
            name="item"
            id="default"
            value=${this.items[0]}
            ?checked=${true}
          />
          ${this.items.map(
            (item, index) =>
              html`<input
                type="radio"
                name="item"
                id=${"item" + (index + 1)}
                value=${item}
                @change="${this._handleChange}"
              />`
          )}
        </summary>
        <ul class="list">
          ${this.items.map(
            (item, index) =>
              html`<li>
                <label for=${"item" + (index + 1)} @click="${this._handleClick}"
                  >${item}</label
                >
              </li>`
          )}
        </ul>
      </details>
    `;
  }

  /**
   * handle input on change
   * @param {Event} e input on change event
   */
  _handleChange(e) {
    // register a custom item selected event
    let selectedEvent = new CustomEvent("item-selected", {
      detail: { option: e.currentTarget.value.toLowerCase() },
      bubbles: true,
      composed: true,
    });
    this.dispatchEvent(selectedEvent);
  }

  /**
   * handle list item clicked
   * @param {Event} e click event
   */
  _handleClick(e) {
    this._details.removeAttribute("open");
  }

  static styles = css`
    :host {
      display: block;
    }
    details {
      position: relative;
      width: 300px;
    }
    details[open] {
      z-index: 1;
    }
    summary {
      display: flex;
      justify-content: space-between;
      align-items: center;
      padding: 1rem;
      cursor: pointer;
      border-radius: 5px;
      background-color: #ddd;
      list-style: none;
    }
    summary::-webkit-details-marker {
      display: none;
    }
    summary:after {
      content: "";
      width: 0.5rem;
      height: 0.5rem;
      border-bottom: 2px solid currentColor;
      border-left: 2px solid currentColor;
      border-bottom-left-radius: 2px;
      transform: rotate(45deg);
      transform-origin: center center;
      transition: transform ease-in-out 100ms;
    }
    summary:focus {
      outline: none;
    }
    details[open] summary:after {
      transform: rotate(-45deg);
    }
    ul {
      width: 100%;
      background: #ddd;
      position: absolute;
      top: calc(100% + 0.5rem);
      left: 0;
      padding: 1rem;
      margin: 0;
      box-sizing: border-box;
      border-radius: 5px;
      max-height: 400px;
      overflow-y: auto;
      list-style-type: none;
    }
    li {
      margin: 0;
      padding: 1rem 0;
      border-bottom: 1px solid #ccc;
    }
    li:first-child {
      padding-top: 0;
    }
    li:last-child {
      padding-bottom: 0;
      border-bottom: none;
    }
    input[type="radio"] {
      appearance: none;
      display: none;
    }
    input[type="radio"]:checked {
      display: block;
    }
    input[type="radio"]:after {
      content: attr(value);
      display: inline;
      font-size: 1rem;
    }
    label {
      width: 100%;
      display: flex;
      cursor: pointer;
      justify-content: space-between;
    }
    @media screen and (max-width: 1900px) {
      details {
        width: 200px;
      }
      summary {
        padding: 0.8rem;
      }
    }
  `;
}

window.customElements.define("select-box", SelectBox);
