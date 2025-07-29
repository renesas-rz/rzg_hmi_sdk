import { LitElement, css, html } from "lit";

/**
 * Class to create Image Gallery page element
 */
export class ImageGalleryPage extends LitElement {
  constructor() {
    super();
  }

  render() {
    return html`
      <div class="container">
        <image-gallery width="960" height="540"></image-gallery>
      </div>
    `;
  }

  static styles = css`
    .container {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100%;
    }
  `;
}

window.customElements.define("image-gallery-page", ImageGalleryPage);
