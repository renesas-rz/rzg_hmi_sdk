import { LitElement, css, html } from "lit";

/**
 * Class to create video player page element
 */
export class VideosPlayerPage extends LitElement {
  constructor() {
    super();
  }

  render() {
    return html`
      <div class="container">
        <video-player width="960" height="540"></video-player>
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

window.customElements.define("videos-player-page", VideosPlayerPage);
