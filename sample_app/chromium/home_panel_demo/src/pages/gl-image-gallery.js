import { LitElement, css, html } from "lit";

/**
 * Class to create WebGL Image Gallery page element
 */
export class GlImageGalleryPage extends LitElement {
  constructor() {
    super();
  }

  render() {
    return html`
      <div class="container">
        <gl-image-slider
          width="960"
          height="540"
          duration="1500"
        ></gl-image-slider>
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
    .container {
      box-sizing: border-box;
    }
  `;
}

window.customElements.define("gl-image-gallery-page", GlImageGalleryPage);
