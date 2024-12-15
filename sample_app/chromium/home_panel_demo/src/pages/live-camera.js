import { LitElement, css, html } from "lit";

/**
 * Class to create Live Camera page element
 */
export class LiveCameraPage extends LitElement {
  constructor() {
    super();
  }

  render() {
    return html` <video-camera></video-camera> `;
  }

  static styles = css`
    :host {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100%;
    }
  `;
}

window.customElements.define("live-camera-page", LiveCameraPage);
