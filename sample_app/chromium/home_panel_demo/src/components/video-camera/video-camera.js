import { LitElement, css, html } from "lit";

export class VideoCamera extends LitElement {
  constructor() {
    super();
    // internal properties
    this._filters = ["Blur", "Grayscale", "Invert", "Sepia"];
  }

  // query the video element in the internal DOM using getter pattern
  get _video() {
    return this.renderRoot.querySelector("video");
  }

  firstUpdated() {
    this._video.className = this._filters[0].toLowerCase();
    navigator.mediaDevices
      .getUserMedia({
        video: true,
      })
      .then((stream) => {
        this._video.srcObject = stream;
      })
      .catch((e) => {
        console.log(e);
      });
  }

  handleFilterSelected(e) {
    this._video.className = e.detail.option;
  }

  render() {
    return html`
      <div class="container">
        <select-box
          .items=${this._filters}
          @item-selected=${this.handleFilterSelected}
        ></select-box>
        <video ?autoplay=${true} id="video"></video>
      </div>
    `;
  }

  static styles = css`
    .container {
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: flex-end;
      gap: 2rem;
    }

    #video {
      border-radius: 2rem;
      width: 1280px;
      height: 720px;
      object-fit: cover;
    }

    .blur {
      -webkit-filter: blur(3px);
      filter: blur(3px);
    }

    .grayscale {
      -webkit-filter: grayscale(1);
      filter: grayscale(1);
    }

    .invert {
      -webkit-filter: invert(1);
      filter: invert(1);
    }

    .sepia {
      -webkit-filter: sepia(1);
      filter: sepia(1);
    }

    @media screen and (max-width: 1900px) {
      #video {
        width: 854px;
        height: 480px;
      }
    }
  `;
}

window.customElements.define("video-camera", VideoCamera);
