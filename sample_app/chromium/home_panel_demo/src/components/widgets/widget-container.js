import { LitElement, css, html } from "lit";
import { classMap } from "lit/directives/class-map.js";

export class WidgetContainer extends LitElement {
  // Define reactive properties
  static properties = {
    // public properties
    // the custom web element's attributes
    isLink: { type: Boolean, reflect: true },
    // internal states
    _active: { state: true },
  };

  constructor() {
    super();
    // set the default value for the element's attributes
    this.isLink = false;
    // set the default internal states
    this._active = false;
  }

  render() {
    // apply classes dynamically
    const linkClasses = {
      // apply "link" class when the given property is set to true
      link: this.isLink,
    };
    return html`
      <div
        class="container${classMap(linkClasses)}"
        @pointerenter=${this.setHover}
        @pointerleave=${this.clearHover}
      >
        <div class="hover-overlay"></div>
        <div class="content">
          <slot></slot>
        </div>
      </div>
    `;
  }

  setHover(event) {
    if (!this.isLink) {
      return;
    }
    event.currentTarget.querySelector(".hover-overlay").style.opacity = "1";
  }

  clearHover(event) {
    if (!this.isLink) {
      return;
    }
    event.currentTarget.querySelector(".hover-overlay").style.opacity = "";
  }

  static styles = css`
    :host {
      display: block;
      height: 100%;
    }
    .container {
      box-sizing: border-box;
      background: var(--widget-background-color, #868e96);
      border-radius: 1rem;
      width: 100%;
      height: 100%;
      display: flex;
      flex-direction: column;
      justify-content: space-between;
      align-items: center;
      padding: var(--widget-padding, 1.5rem);
      position: relative;
      overflow: hidden;
    }
    .hover-overlay {
      position: absolute;
      inset: 0;
      background: var(--widget-hover-background-color, #6a6c6e);
      opacity: 0;
      pointer-events: none;
      z-index: 0;
      will-change: opacity;
    }
    .content {
      display: flex;
      flex-direction: column;
      justify-content: space-between;
      align-items: center;
      width: 100%;
      height: 100%;
      position: relative;
      z-index: 1;
    }
    @media screen and (max-width: 1900px) {
      .container {
        padding: var(--widget-padding, 1rem);
      }
    }
  `;
}

window.customElements.define("widget-container", WidgetContainer);
