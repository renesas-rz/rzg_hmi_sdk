import { LitElement, css, html } from "lit";
import { WebGLSlider } from "./gl-slider";

export class GlImageSlider extends LitElement {
  // Define reactive properties
  static properties = {
    // public properties
    // the custom web element's attributes
    width: { type: Number },
    height: { type: Number },
    duration: { type: Number },
    // internal states
    _transition_type: { state: true },
    _transtion_type_index: { state: true },
    _currIndex: { state: true },
  };

  constructor() {
    super();
    // set the default value for the element's attributes
    this.width = undefined;
    this.height = undefined;
    this.slider = null;
    this.duration = 1000;
    this.imgSrcs = [
      "/img/photo_0.jpg",
      "/img/photo_1.jpg",
      "/img/photo_2.jpg",
      "/img/photo_3.jpg",
    ];
    this.transition_types = [
      "random",
      "cube",
      "WaterDrop",
      "pixelize",
      "GridFlip",
      "rotate_scale_fade",
    ];

    // set the default internal states
    this._transition_type = "random";
    this._transtion_type_index = 0;
    this._currIndex = 0;
  }

  // Invoked when the custom element is initially rendered
  firstUpdated() {
    // query the canvas element in the internal DOM
    const canvas = this.renderRoot.querySelector("#slider");
    canvas.width = this.width;
    canvas.height = this.height;

    // create the WebGL slider
    this.slider = new WebGLSlider(this.duration, canvas, this.imgSrcs);
  }

  _handleSelection() {
    if (this._transtion_type_index < this.transition_types.length - 1) {
      this._transtion_type_index += 1;
    } else {
      this._transtion_type_index = 0;
    }
    this._transition_type = this.transition_types[this._transtion_type_index];
  }

  _handleThumbClick(index) {
    if (this.slider._isActive) return 0;

    this.slider.fromIndex = this._currIndex;
    this.slider.toIndex = index;

    if (this._transition_type === "random") {
      this.slider.transitionType = this._getRandomTransition();
    } else {
      this.slider.transitionType = this._transition_type;
    }

    this.slider.start();

    this._currIndex = index;
  }

  _getRandomTransition() {
    const filtered = this.transition_types.filter((item) => item !== "random");
    return filtered[[Math.floor(Math.random() * filtered.length)]];
  }

  render() {
    return html`
      <header>
        <span>Transition</span>
        <span id="transition_selection" @click=${this._handleSelection}>
          ${this._transition_type}
        </span>
      </header>
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
        <canvas id="slider"></canvas>
      </main>
    `;
  }

  static styles = css`
    :host {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }
    header {
      margin-bottom: 1rem;
      font-size: 1.8rem;
    }
    header span:first-child {
      color: #2f419a;
      font-weight: bold;
    }
    #transition_selection {
      display: inline-flex;
      align-items: center;
      padding: 3px 12px;
      border: 1px solid #e3e1ff;
      background-color: #2f419a;
      border-radius: 12px;
      color: white;
      cursor: pointer;
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

window.customElements.define("gl-image-slider", GlImageSlider);
