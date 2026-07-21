import { LitElement, css, html } from "lit";

/**
 * Class to create video player page element
 */
export class VideosPlayerH265Page extends LitElement {
  constructor() {
    super();
  }

  render() {
    return html`
      <div class="container">
        <video-player_h.265 width="960" height="540"></video-player_h.265>
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

window.customElements.define("videos-player-h.265-page", VideosPlayerH265Page);
