import GLTransitions from "gl-transitions";
import createTransition from "gl-transition";
import createTexture from "gl-texture2d";

export class WebGLSlider {
  constructor(duration, canvas, imgSrcs) {
    // internal private properties
    this._gl = this._setupWebGL(canvas);
    this._duration = duration;
    this._canvas = canvas;
    this._imgSrcs = imgSrcs;
    this._slides = null;
    this._fromIndex = 0;
    this._toIndex = 0;
    this._transitionType = "cube";
    this._then = 0;
    this._currTime = 0;
    this._progress = 0;
    this._isActive = false;

    // Initiate the slider
    this._initSlider();
  }

  set transitionType(val) {
    this._transitionType = val;
  }

  get transitionType() {
    return this._transitionType;
  }

  set fromIndex(val) {
    this._fromIndex = val;
  }

  get fromIndex() {
    return this._fromIndex;
  }

  set toIndex(val) {
    this._toIndex = val;
  }

  get toIndex() {
    return this._toIndex;
  }

  /**
   * load the image from src asynchronously
   * @param {string} src the path where the image is located
   * @returns {object} promise
   */
  _loadImage = (src) =>
    new Promise((resolve, reject) => {
      const img = new Image();
      img.onload = () => resolve(img);
      img.onerror = reject;
      img.onabort = reject;
      img.src = src;
      img.crossOrigin = "anonymous";
    });

  /**
   * Create a WebGL context from the given canvas
   * @param {HTMLCanvasElement} canvas the canvas
   * @returns {object} WebGL context
   */
  _setupWebGL = (canvas) => {
    const gl = canvas.getContext("webgl");

    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
    const buffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
    gl.bufferData(
      gl.ARRAY_BUFFER,
      new Float32Array([-1, -1, -1, 4, 4, -1]), // see a-big-triangle
      gl.STATIC_DRAW
    );
    gl.viewport(0, 0, canvas.width, canvas.height);

    return gl;
  };

  /**
   * Find the transition type we want
   */
  _setupGlTransition = () =>
    GLTransitions.find((t) => t.name === this._transitionType);

  /**
   * Init the image slider
   */
  _initSlider = async () => {
    this.transition = this._setupGlTransition();
    const transition = createTransition(this._gl, this.transition);
    const slides = await this._createSlides();
    transition.draw(
      0,
      slides[0],
      slides[0],
      this._canvas.width,
      this._canvas.height,
      {}
    );
  };

  /**
   * Create the transition animation
   * @param {object} slides the canvas
   * @param {object} transition the transition
   */
  _animateTransition = (slides, transition) => {
    const render = (timestamp) => {
      // compare the timestamp with the previous value
      if (!this._then) this._then = timestamp;
      // calculate the difference
      const deltaTime = timestamp - this._then;
      this._then = timestamp;

      const from = slides[this._fromIndex];
      const to = slides[this._toIndex];

      // When the transition is in progress
      if (this._isActive) {
        this._progress = this._currTime / this._duration;
        this._currTime += deltaTime;
        transition.draw(
          this._progress,
          from,
          to,
          this._canvas.width,
          this._canvas.height,
          {}
        );
      }

      // When the transition is finished
      if (this._progress > 1) {
        this._isActive = false;
        this._progress = 0;
        this._currTime = 0;
        transition.draw(
          1,
          from,
          to,
          this._canvas.width,
          this._canvas.height,
          {}
        );
      }

      requestAnimationFrame(render);
    };
    requestAnimationFrame(render);
  };

  /**
   * Create the image slides
   * @returns {object} WebGL textures
   */
  _createSlides = async () => {
    const images = await Promise.all(this._imgSrcs.map(this._loadImage));
    return images.map((img) => createTexture(this._gl, img));
  };

  /**
   * Start the animation
   */
  start = async () => {
    this._slides = await this._createSlides();
    this.transition = this._setupGlTransition();
    const transition = createTransition(this._gl, this.transition);
    this._isActive = true;
    this._animateTransition(this._slides, transition);
  };
}
