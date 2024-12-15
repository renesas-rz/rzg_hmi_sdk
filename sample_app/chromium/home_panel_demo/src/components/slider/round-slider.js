import { LitElement, html, css, svg } from "lit";

export class RoundSlider extends LitElement {
  // Define reactive properties
  static properties = {
    // public properties
    // the custom web element's attributes
    value: { type: Number },
    min: { type: Number },
    max: { type: Number },
    step: { type: Number },
    startAngle: { type: Number },
    arcLength: { type: Number },
    sliderWidth: { type: Number },
    valueRadius: { type: Number },
    valueLabel: { type: String },
    disabled: { type: Boolean, reflect: true },
    dragging: { type: Boolean, reflect: true },
  };

  constructor() {
    super();
    // set the default value for the element's attributes
    this.value = null;
    this.min = 0;
    this.max = 100;
    this.step = 1;
    this.startAngle = 180;
    this.arcLength = 180;
    this.sliderWidth = 1;
    this.valueRadius = 0.6;
    this.valueLabel = "";
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

  get _start() {
    return this.startAngle * (Math.PI / 180);
  }

  get _len() {
    // Things get weird if length is more than a complete turn
    return Math.min((this.arcLength * Math.PI) / 180, 2 * Math.PI - 0.01);
  }

  get _end() {
    return this._start + this._len;
  }

  /**
   * Check if an angle is on the arc
   * @param {number} angle angle between 0-360 to be checked
   * @returns {boolean} true or false
   */
  _angleInside(angle) {
    let a =
      ((this.startAngle + this.arcLength / 2 - angle + 180 + 360) % 360) - 180;
    return a < this.arcLength / 2 && a > -this.arcLength / 2;
  }

  /**
   * Convert a particular angle into x and y position
   * @param {number} angle a particular angle to be converted to
   * @returns {object} converted x and y position
   */
  _angle2xy(angle) {
    return { x: Math.cos(angle), y: Math.sin(angle) };
  }

  /**
   * Convert x and y position into a particular angle
   * @param {number} x the x position
   * @param {number} y the y position
   * @returns {number} converted angle value
   */
  _xy2angle(x, y) {
    return (Math.atan2(y, x) - this._start + 8 * Math.PI) % (2 * Math.PI);
  }

  /**
   * Convert the slider value into a particular angle
   * @param {number} value the slider value
   * @returns {number} converted angle value
   */
  _value2angle(value) {
    value = Math.min(this.max, Math.max(this.min, value));
    const fraction = (value - this.min) / (this.max - this.min);
    return this._start + fraction * this._len;
  }

  /**
   * Convert a particular angle into the slider value
   * @param {number} angle a particular angle
   * @returns {number} converted slider value
   */
  _angle2value(angle) {
    return (
      Math.round(
        ((angle / this._len) * (this.max - this.min) + this.min) / this.step
      ) * this.step
    );
  }

  /**
   * Get the boundary of the SVG.
   * The value is used to set the viewport.
   */
  get _boundaries() {
    // Get the maximum extents of the bar arc
    const start = this._angle2xy(this._start);
    const end = this._angle2xy(this._end);
    let up = 1;
    if (!this._angleInside(270)) up = Math.round(Math.max(-start.y, -end.y));
    let down = 1;
    if (!this._angleInside(90)) down = Math.round(Math.max(start.y, end.y));
    let left = 1;
    if (!this._angleInside(180)) left = Math.round(Math.max(-start.x, -end.x));
    let right = 1;
    if (!this._angleInside(0)) right = Math.round(Math.max(start.x, end.x));
    return {
      up,
      down,
      left,
      right,
      height: up + down,
      width: left + right,
    };
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
    const mouseY = ev.type.startsWith("touch")
      ? ev.touches[0].clientY
      : ev.clientY;
    const rect = this.renderRoot.querySelector("svg").getBoundingClientRect();
    const boundaries = this._boundaries;
    const x =
      mouseX - (rect.left + (boundaries.left * rect.width) / boundaries.width);
    const y =
      mouseY - (rect.top + (boundaries.up * rect.height) / boundaries.height);
    const angle = this._xy2angle(x, y);
    const pos = this._angle2value(angle);
    return pos;
  }

  /**
   * Handle mouse down and touch start event
   * @param {Event} ev mouse/touch event
   */
  dragStart(ev) {
    if (this.disabled) return;
    let handle = ev.target;
    // Avoid double events mouseDown->focus
    if (this._rotation && this._rotation.type !== "focus") return;
    if (!handle.classList.contains("handle")) return;

    this._rotation = {
      handle,
      min: this.min,
      max: this.max,
      start: this[handle.id],
      type: ev.type,
    };
    this.dragging = true;
  }

  /**
   * Handle mouse up and touch end event
   * @param {Event} ev mouse/touch event
   */
  dragEnd = (_ev) => {
    if (this.disabled) return;
    if (!this._rotation) return;
    const handle = this._rotation.handle;
    this._cleanupRotation();
    let event = new CustomEvent("value-changed", {
      detail: {
        [handle.id]: this[handle.id],
      },
      bubbles: true,
      composed: true,
    });
    this.dispatchEvent(event);
  };

  /**
   * Handle mouse move and touch move event
   * @param {Event} ev mouse/touch event
   */
  drag = (ev) => {
    if (this.disabled) return;
    if (!this._rotation) return;
    if (this._rotation.type === "focus") return;
    ev.preventDefault();
    const pos = this._mouse2value(ev);
    this._dragpos(pos);
  };

  /**
   * Update the slider value
   * @param {number} pos mouse position relative to the SVG's bounding rect
   */
  _dragpos(pos) {
    if (pos < this._rotation.min || pos > this._rotation.max) return;
    const handle = this._rotation.handle;
    this[handle.id] = pos;
    // register a custom event when the value is changed
    let event = new CustomEvent("value-changing", {
      detail: {
        [handle.id]: pos,
      },
      bubbles: true,
      composed: true,
    });
    // dispatch the custom event
    this.dispatchEvent(event);
  }

  /**
   * Cleanup after drag
   */
  _cleanupRotation() {
    const handle = this._rotation.handle;
    this._rotation = undefined;
    this.dragging = false;
    handle.blur();
  }

  /**
   * Render the arc slider bar
   */
  _renderArc(start, end, offset) {
    const diff = end - start;
    const startXY = this._angle2xy(start);
    const endXY = this._angle2xy(end);
    return `
      M ${startXY.x - offset} ${startXY.y}
      A 1 1,
        0,
        ${diff > Math.PI ? "1" : "0"} 1,
        ${endXY.x + offset} ${endXY.y}
    `;
  }

  /**
   * Render the slider ticks
   */
  _renderTicks(isMajor) {
    const scale = isMajor ? 1 : 10;

    const ticksTemplates = [];

    for (let i = 0; i <= (this.max - this.min) * scale; i++) {
      ticksTemplates.push(svg`
				<line 
					x1=${this._boundaries.width / 2 - 0.12}
					y1="0" 
					x2=${this._boundaries.width / 2 - (isMajor ? 0.15 : 0.11)} 
					y2="0" 
					stroke="#999" 
					stroke-width="0.01" 
					transform="rotate(-${i * (this.arcLength / ((this.max - this.min) * scale))})"
				/>
			`);
    }

    return ticksTemplates;
  }

  render() {
    const view = this._boundaries;
    const theta = this._value2angle(this.value);
    const pos = this._angle2xy(theta);
    const label = this.valueLabel || "";

    return html`
      <svg
        @mousedown=${this.dragStart}
        @touchstart=${this.dragStart}
        xmln="http://www.w3.org/2000/svg"
        style="margin: ${this.sliderWidth}px ${this.sliderWidth}px 0px ${this
          .sliderWidth}px;"
        viewBox="${-view.left} ${-view.up} ${view.width} ${view.height +
        this.valueRadius}"
        ?disabled=${this.disabled}
        focusable="false"
      >
        <defs>
          <linearGradient id="linear" x1="0%" y1="0%" x2="100%" y2="0%">
            <stop offset="0%" stop-color="#42a6f8" />
            <stop offset="50%" stop-color="#80f342" />
            <stop offset="90%" stop-color="#ffe500" />
            <stop offset="100%" stop-color="#ffae00" />
          </linearGradient>
        </defs>
        <g class="value">
          <circle
            class="value"
            r=${this.valueRadius}
            vector-effect="non-scaling-stroke"
            tabindex="0"
            fill-opacity="0.8"
          />
          <text
            x="0"
            y="0"
            text-anchor="middle"
            alignment-baseline="middle"
            font-size="0.35"
            fill="white"
          >
            ${this.value.toFixed(1)}°
          </text>
        </g>
        <g class="slider">
          <path
            id="slider-arc"
            d=${this._renderArc(this._start, this._end, 0.12)}
            vector-effect="non-scaling-stroke"
          />

          <text font-size="0.1" fill="white">
            <textPath href="#slider-arc" startOffset="0%">15</textPath>
            <textPath href="#slider-arc" startOffset="31%">20</textPath>
            <textPath href="#slider-arc" startOffset="66%">25</textPath>
            <textPath href="#slider-arc" startOffset="97%">30</textPath>
          </text>

          <path
            class="path"
            d=${this._renderArc(this._start, this._end, 0)}
            vector-effect="non-scaling-stroke"
            stroke-width="${this.sliderWidth * 2}"
            stroke="url(#linear)"
          />

          ${this._renderTicks(true)} ${this._renderTicks(false)}
        </g>

        <g class="handle">
          <circle
            id="value"
            class="handle"
            cx=${pos.x}
            cy=${pos.y}
            r=${this.sliderWidth / 100}
            stroke-width="0"
            vector-effect="non-scaling-stroke"
            tabindex="0"
            role="slider"
            aria-valuemin=${this.min}
            aria-valuemax=${this.max}
            aria-valuenow=${this.value}
            aria-disabled=${this.disabled}
            aria-label=${label}
          />
        </g>
      </svg>
    `;
  }

  static styles = css`
    :host {
      display: inline-block;
      width: 100%;
    }
    svg {
      overflow: visible;
      display: block;
    }
    path {
      transition: stroke 1s ease-out, stroke-width 500ms ease-out;
    }
    .value {
      fill: var(--round-slider-value-color, #333);
    }
    .slider {
      fill: none;
      stroke-width: var(--round-slider-path-width, 3);
      stroke-linecap: var(--round-slider-linecap, round);
    }
    .handle {
      fill: var(--round-slider-handle-color, white);
      cursor: var(--round-slider-handle-cursor, pointer);
      transition: stroke 500ms ease-out, fill 1s ease-out;
    }
    svg[disabled] .path {
      stroke: var(--round-slider-disabled-arc-color, darkgray);
      transition: stroke 500ms ease-out;
    }
    svg[disabled] .handle {
      fill: var(--round-slider-disabled-arc-color, #555);
      stroke: var(--round-slider-disabled-arc-color, darkgray);
      transition: stroke 500ms ease-out, fill 500ms ease-out;
    }
    .handle:focus {
      outline: unset;
    }
  `;
}

window.customElements.define("round-slider", RoundSlider);
