import { LitElement, css, html, nothing } from "lit";
import { classMap } from "lit/directives/class-map.js";

export class ListItems extends LitElement {
  // Define reactive properties
  static properties = {
    // public properties
    // the custom web element's attributes
    items: { type: Array },
    location: { type: Object },
  };

  constructor() {
    super();
    // set the default value for the element's attributes
    this.items = null;
    this.location = null;
  }

  render() {
    return this.items.map((item) => {
      // apply classes dynamically
      const disabledClasses = {
        // apply "disabled" class when the given item is set to disabled
        disabled: item.disabled,
      };
      const activeClasses = {
        // apply "active" class when the given item's href prop is equal to the URL location
        active: this.location === item.href,
      };
      return html`
        <li class=${(classMap(disabledClasses), classMap(activeClasses))}>
          <a href=${!item.disabled ? item.href : nothing}>
            ${item.svg}
            <span>${item.title}</span>
          </a>
        </li>
      `;
    });
  }

  static styles = css`
    :host {
      display: block;
    }
    li {
      font-size: 1.8rem;
      width: 310px;
    }
    a {
      padding: 0.5rem;
      text-decoration: none;
      color: #e6e6ef;
      display: flex;
      align-items: center;
      gap: 1rem;
    }
    a span {
      flex-grow: 1;
    }
    li.active a {
      color: #5e63ff;
    }
    li.active a svg {
      fill: #5e63ff;
    }
    li.disabled a {
      color: #868e96;
    }
    li.disabled a svg {
      fill: #868e96;
    }
    svg {
      flex-shrink: 0;
      width: 2rem;
      height: 2rem;
      fill: #e6e6ef;
    }

    @media screen and (max-width: 1900px) {
      li {
        font-size: 1.5rem;
        width: 270px;
      }
      svg {
        width: 36px;
        height: 36px;
      }
    }
  `;
}

window.customElements.define("list-items", ListItems);
