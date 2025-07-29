import { LitElement, css, html } from "lit";

export class ImageGallery extends LitElement {
  constructor() {
    super();

    this.imgSrcs = [
      "/img/photo_0.jpg",
      "/img/photo_1.jpg",
      "/img/photo_2.jpg",
      "/img/photo_3.jpg",
    ];
  }

  _handleThumbClick(index) {
    if (index == "0") {
      this.renderRoot.querySelector("#center").src = this.imgSrcs[0];
    } else if (index == "1") {
      this.renderRoot.querySelector("#center").src = this.imgSrcs[1];
    } else if (index == "2") {
      this.renderRoot.querySelector("#center").src = this.imgSrcs[2];
    } else if (index == "3") {
      this.renderRoot.querySelector("#center").src = this.imgSrcs[3];
    }
  }

  render() {
    return html`
      <main class="container">
        <div class="thumbnails">
          <div class="img" @click=${() => this._handleThumbClick(0)}>
            <img src=${this.imgSrcs[0]} alt="" />
          </div>
          <div class="img" @click=${() => this._handleThumbClick(1)}>
            <img src=${this.imgSrcs[1]} alt="" />
          </div>
          <div class="img" @click=${() => this._handleThumbClick(2)}>
            <img src=${this.imgSrcs[2]} alt="" />
          </div>
          <div class="img" @click=${() => this._handleThumbClick(3)}>
            <img src=${this.imgSrcs[3]} alt="" />
          </div>
        </div>
        <img src=${this.imgSrcs[0]} id="center" />
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
      display: flex;
      gap: 1rem;
    }
    .thumbnails {
      display: flex;
      flex-direction: column;
      justify-content: space-between;
    }
    .img {
      cursor: pointer;
      height: 120px;
    }
    .img img {
      object-fit: cover;
      height: 100%;
      width: 210px;
      border-radius: 10px;
    }
  `;
}

window.customElements.define("image-gallery", ImageGallery);
