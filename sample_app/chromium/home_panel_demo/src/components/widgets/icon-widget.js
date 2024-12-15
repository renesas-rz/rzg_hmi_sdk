import { LitElement, css, html } from "lit";

export class IconWidget extends LitElement {
  // Define reactive properties
  static properties = {
    // public properties
    // the custom web element's attributes
    title: { type: String },
    href: { type: String },
  };

  constructor() {
    super();
    // set the default value for the element's attributes
    this.title = "title";
    this.href = "/";
  }

  render() {
    return html`
      <a href=${this.href}>
        <widget-container isLink>
          <slot></slot>
          <span class="widget-title">${this.title}</span>
        </widget-container>
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
    .widget-title {
      color: #ddd;
      font-size: var(--widget-font-size, 2rem);
    }
    @media screen and (max-height: 800px) {
      .widget-title {
        font-size: var(--widget-font-size, 1rem);
      }
    }
  `;
}

window.customElements.define("icon-widget", IconWidget);
