import { LitElement, css, html } from "lit";

export class VideoPlayer extends LitElement {
  constructor() {
    super();

    this.imgSrcs = ["/img/cat.png", "/img/beach.png", "/img/flower.png"];

    this.videoSrcs = [
      "/video/cat.mp4",
      "/video/beach.mp4",
      "/video/flower.mp4",
    ];
  }

  _handleThumbClick(index) {
    if (index == "0") {
      this.renderRoot.querySelector("#big-video").src = this.videoSrcs[0];
    } else if (index == "1") {
      this.renderRoot.querySelector("#big-video").src = this.videoSrcs[1];
    } else if (index == "2") {
      this.renderRoot.querySelector("#big-video").src = this.videoSrcs[2];
    }
  }

  render() {
    return html`
      <main class="container">
        <div class="thumbnails">
          <div class="img" @click=${() => this._handleThumbClick(0)}>
            <img src=${this.imgSrcs[0]} />
          </div>
          <br />
          <div class="img" @click=${() => this._handleThumbClick(1)}>
            <img src=${this.imgSrcs[1]} />
          </div>
          <br />
          <div class="img" @click=${() => this._handleThumbClick(2)}>
            <img src=${this.imgSrcs[2]} />
          </div>
        </div>
        <video
          controls
          id="big-video"
          src=${this.videoSrcs[0]}
        ></video>
      </main>
    `;
  }

  static styles = css`
    :host {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }

    .container {
      width: 100%;
      display: flex;
      gap: 1rem;
    }

    .thumbnails {
      display: flex;
      flex-direction: column;
      justify-content: space-around;
    }
    .img {
      cursor: pointer;
      height: 145px;
    }
    .img img {
      object-fit: cover;
      height: 100%;
      width: 210px;
      border-radius: 10px;
    }

    video {
      width: 870px;
      height: 500px;
    }
    #big-video {
      z-index: 1;
    }

    #label {
      background-color: white;
      width: 16px;
      height: 20px;
      margin: 0 5px;
    }

    .controls {
      position: relative;
      height: 28px;
      z-index: 2;
      bottom: 0;
      width: 99%;
      background: rgba(0, 0, 0, 0.6);
      display: flex;
      align-items: center;
      padding: 5px;
      margin-top: 500px;
    }
    .controls button,
    .controls input.seek[type="range"] {
      margin: 0 5px;
    }
    .controls input.seek[type="range"] {
      flex: 1;
      width: 600px;
    }
  `;
}

window.customElements.define("video-player", VideoPlayer);
