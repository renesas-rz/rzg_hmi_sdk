import { LitElement, css, html } from "lit";

export class ProgressWidget extends LitElement {
  // Define reactive properties
  static properties = {
    // public properties
    // the custom web element's attributes
    title: { type: String },
    value: { type: Number },
    max: { type: Number },
    unit: { type: String },
    duration: { type: Number },
    // internal states
    _counter: { state: true },
    _cx: { state: true },
    _cy: { state: true },
    _r: { state: true },
    _dashArray: { state: true },
  };

  constructor() {
    super();
    // set the default value for the element's attributes
    this.title = "title";
    this.value = 65;
    this.max = 100;
    this.unit = "%";
    this.duration = 80;
    this.resizeObserver = null;
    // set the default internal states
    this._cx = 80;
    this._cy = 80;
    this._r = 70;
    this._dashArray = 440;
    this._counter = 0;
  }

  // Invoked when the custom element is added to the document's DOM.
  connectedCallback() {
    super.connectedCallback();

    // Animate the progress value
    this.interval = setInterval(() => {
      if (this._counter === this.value) {
        clearInterval;
      } else {
        this._counter += Math.ceil(this.max / 100);
      }
    }, this.duration);
  }

  // Invoked when the custom element is removed from the document's DOM.
  disconnectedCallback() {
    super.disconnectedCallback();

    // Always clear the interval
    // whenever the element is removed from the document's DOM
    clearInterval(this.interval);
  }

  // Invoked when the custom element is initially rendered
  firstUpdated() {
    // query internal DOM
    const container = this.shadowRoot.querySelector("widget-container");
    const svgAnimateEl = this.shadowRoot.querySelector("svg animate");

    // Setup the resizeObserver
    const resizeObserver = new ResizeObserver((entries) => {
      entries.forEach((entry) => {
        if (entry.contentBoxSize) {
          const contentBoxSize = entry.contentBoxSize[0];
          // start the SVG animation whenever the change in size of
          // the container is observed
          svgAnimateEl.beginElement();

          // resize the progress bar whenever the change in size of
          // the container is obeserved
          if (contentBoxSize.inlineSize < 240) {
            this._cx = 50;
            this._cy = 50;
            this._r = 43;
            this._dashArray = 280;
          } else {
            this._cx = 80;
            this._cy = 80;
            this._r = 70;
            this._dashArray = 440;
          }
        }
      });
    });

    // observe the size of the container
    resizeObserver.observe(container);
  }

  render() {
    return html`
      <widget-container>
        <span class="widget-title">${this.title}</span>
        <div class="progress-bar">
          <div class="outer">
            <div class="value">${this._counter}${this.unit}</div>
          </div>
          <svg xmlns="http://www.w3.org/2000/svg">
            <circle
              fill="none"
              cx=${this._cx}
              cy=${this._cy}
              r=${this._r}
              stroke-linecap="round"
              stroke-dasharray=${this._dashArray}
              stroke-dashoffset=${this._dashArray -
              (this.value / this.max) * this._dashArray}
            >
              <animate
                attributeName="stroke-dashoffset"
                begin="indefinite"
                dur="${Math.ceil(this.max / this.value)}s"
                from=${this._dashArray}
                to=${this._dashArray -
                (this.value / this.max) * this._dashArray}
                fill="freeze"
              />
            </circle>
          </svg>
        </div>
      </widget-container>
    `;
  }

  static styles = css`
    :host {
      display: block;
    }
    a {
      text-decoration: none;
    }
    .widget-title {
      color: #ddd;
      font-size: var(--widget-font-size, 1.5rem);
    }
    .progress-bar {
      width: 160px;
      height: 160px;
      position: relative;
    }
    .progress-bar svg {
      width: 160px;
      height: 160px;
      transform: rotate(-90deg);
      position: absolute;
      top: 0;
      left: 0;
    }
    .outer {
      box-sizing: border-box;
      width: 160px;
      height: 160px;
      border-radius: 50%;
      border: solid 20px #ddd;
      display: flex;
      justify-content: center;
      align-items: center;
      box-shadow: 6px 6px 10px -1px rgba(0, 0, 0, 0.15),
        -6px -6px 10px -1px rgba(255, 255, 255, 0.2);
    }
    .value {
      font-size: 1.5rem;
      font-weight: bold;
      color: #ccc;
    }
    circle {
      stroke: var(--widget-progress-bar-color, #ddd);
      stroke-width: 20px;
    }
    @media screen and (max-width: 1900px) {
      .progress-bar {
        width: 100px;
        height: 100px;
      }
      .outer {
        width: 100px;
        height: 100px;
      }
      .widget-title {
        font-size: var(--widget-font-size, 1rem);
      }
      .progress-bar svg {
        width: 100px;
        height: 100px;
      }
      .outer {
        border: solid 15px #ddd;
      }
      .value {
        font-size: 0.8rem;
      }
      circle {
        stroke-width: 15px;
      }
    }
  `;
}

window.customElements.define("progress-widget", ProgressWidget);
