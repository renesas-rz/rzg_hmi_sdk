import { LitElement, css, html } from "lit";

export class Slider extends LitElement {
  // Define reactive properties
  static properties = {
    // public properties
    // the custom web element's attributes
    value: { type: Number },
    min: { type: Number },
    max: { type: Number },
    color1: { type: String },
    color2: { type: String },
    color3: { type: String },
    handleLength: { type: Number },
    sliderWidth: { type: Number },
    sliderHeight: { type: Number },
    unit: { type: String },
    disabled: { type: Boolean, reflect: true },
    dragging: { type: Boolean, reflect: true },
  };

  constructor() {
    super();
    // set the default value for the element's attributes
    this.value = null;
    this.min = 0;
    this.max = 100;
    this.color1 = "#6053a7";
    this.color2 = "#00b0ea";
    this.color3 = "#4cf8b2";
    this.handleLength = 30;
    this.handleOffset = 0;
    this.sliderWidth = 200;
    this.sliderHeight = 40;
    this.unit = "";
    this.disabled = false;
    this.dragging = false;
  }

  // Invoked when the custom element is added to the document's DOM.
  connectedCallback() {
    super.connectedCallback();

    // add mouse and touch event listener to the window object
    // when the component is added to the document's DOM.
    window.addEventListener("mouseup", this.dragEnd);
    window.addEventListener("touchend", this.dragEnd, {
      passive: false,
    });
    window.addEventListener("mousemove", this.drag);
    window.addEventListener("touchmove", this.drag, {
      passive: false,
    });
  }

  // Invoked when the custom element is removed from the document's DOM.
  disconnectedCallback() {
    super.disconnectedCallback();

    // remove mouse and touch event listener to the window object
    // when the component is removed to the document's DOM.
    window.removeEventListener("mouseup", this.dragEnd);
    window.removeEventListener("touchend", this.dragEnd);
    window.removeEventListener("mousemove", this.drag);
    window.removeEventListener("touchmove", this.drag);
  }

  /**
   * Get the mouse position inside the SVG
   * @param {Event} ev mouse/touch event
   * @returns {number} mouse position relative to the SVG's bounding rect
   */
  _mouse2value(ev) {
    const mouseX = ev.type.startsWith("touch")
      ? ev.touches[0].clientX
      : ev.clientX;
    const rect = this.shadowRoot.querySelector("svg").getBoundingClientRect();

    return Math.round(mouseX - rect.left - this.handleOffset);
  }

  /**
   * Handle mouse down and touch start event
   * @param {Event} ev mouse/touch event
   */
  dragStart(ev) {
    if (this.disabled) return;
    let handle = ev.target;
    const mouseX = ev.type.startsWith("touch")
      ? ev.touches[0].clientX
      : ev.clientX;
    if (!handle.classList.contains("handle")) return;

    const handleRect = this.shadowRoot
      .querySelector("#value")
      .getBoundingClientRect();
    this.handleOffset = mouseX - handleRect.left;

    this._movement = {
      handle,
      min: this.min,
      max: (this.sliderWidth / this.max) * this.max - this.handleLength,
      type: ev.type,
    };

    this.dragging = true;
  }

  /**
   * Cleanup after drag
   */
  _cleanupMovement() {
    const handle = this._movement.handle;
    this._movement = undefined;
    this.dragging = false;
    handle.blur();
  }

  /**
   * Handle mouse up and touch end event
   * @param {Event} ev mouse/touch event
   */
  dragEnd = (_ev) => {
    if (this.disabled) return;
    if (!this._movement) return;
    this._cleanupMovement();
  };

  /**
   * Handle mouse move and touch move event
   * @param {Event} ev mouse/touch event
   */
  drag = (ev) => {
    if (this.disabled) return;
    if (!this._movement) return;
    if (this._movement.type === "focus") return;
    ev.preventDefault();
    const pos = this._mouse2value(ev);
    this._dragpos(pos);
  };

  /**
   * Update the slider value
   * @param {number} pos mouse position relative to the SVG's bounding rect
   */
  _dragpos(pos) {
    if (pos < this._movement.min || pos > this._movement.max) return;
    this.value = pos;
    this.displayValue = this.value * (this.max / this._movement.max);
  }

  render() {
    return html`
      <div class="container">
        <svg
          @mousedown=${this.dragStart}
          @touchstart=${this.dragStart}
          height=${this.sliderHeight}
          viewBox="0 0 ${this.sliderWidth} ${this.sliderHeight}"
          xmlns="http://www.w3.org/2000/svg"
          ?disabled=${this.disabled}
          focusable="false"
        >
          <defs>
            <linearGradient id="gradient1" x1="0%" x2="100%" y1="0%" y2="0%">
              <stop offset="0%" stop-color=${this.color1} />
              <stop offset="50%" stop-color=${this.color2} />
              <stop offset="100%" stop-color=${this.color3} />
            </linearGradient>
          </defs>
          <g>
            <rect
              width="100%"
              height="100%"
              rx="${this.sliderHeight / 2}"
              fill="#333"
            />
            <rect
              class="rect"
              width="${this.value + this.handleLength}"
              height="100%"
              rx="${this.sliderHeight / 2}"
              fill="url(#gradient1)"
              stroke-width="0"
            />
            <g>
              <rect
                id="value"
                class="handle"
                stroke-width="0"
                width="${this.handleLength}"
                height="100%"
                x="${this.value}"
                rx="${this.sliderHeight / 2}"
                aria-disabled=${this.disabled}
              />
            </g>
          </g>
        </svg>
        <span
          class="value"
          style="width: ${this.sliderHeight + 5}px; height: ${this
            .sliderHeight}px;"
        >
          ${this.displayValue ? this.displayValue : this.value}${this.unit}
        </span>
      </div>
    `;
  }

  static styles = css`
    :host {
      display: block;
    }
    .handle {
      fill: var(--slider-handle-color, white);
      cursor: var(--slider-handle-cursor, pointer);
      transition: stroke 500ms ease-out, fill 500ms ease-out;
    }
    svg[disabled] .rect {
      fill: var(--slider-disabled-arc-color, darkgray);
      transition: fill 500ms ease-out;
    }
    svg[disabled] .handle {
      fill: var(--slider-disabled-arc-color, #555);
      stroke: var(--slider-disabled-arc-color, darkgray);
      transition: stroke 500ms ease-out, fill 500ms ease-out;
    }
    .handle:focus {
      outline: unset;
    }
    .container {
      display: flex;
      align-items: center;
      gap: 0.8rem;
    }
    .value {
      display: flex;
      justify-content: center;
      align-items: center;
      font-size: 0.75em;
      color: #666;
      font-weight: bold;
      background-color: #fff;
      border-radius: 2em;
    }
  `;
}

window.customElements.define("input-slider", Slider);
