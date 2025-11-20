from flask import Flask, request, jsonify
import subprocess
import json
import time

app = Flask(__name__)

@app.route("/api/reduce", methods=["POST"])
def reduce_values():
    try:
        data = request.get_json()
        values = data.get("values", [])

        if not isinstance(values, list) or not values:
            return jsonify({"error": "Invalid 'values' input"}), 400

        # Convert list → temp JSON for CUDA program (optional)
        input_json = json.dumps(values)

        # ---------------------------------------------
        # CPU Reduction (baseline)
        # ---------------------------------------------
        cpu_start = time.time()
        total_sum = sum(values)
        avg = total_sum / len(values)
        mn = min(values)
        mx = max(values)
        cpu_end = time.time()

        cpu_ms = (cpu_end - cpu_start) * 1000

        # ---------------------------------------------
        # GPU Reduction (only runs with you ANGELO)
        # ---------------------------------------------
        try:
            gpu_start = time.time()

            # Call CUDA executable (built by your friend)
            # Example:
            # output = subprocess.check_output(["./cuda_reduce", input_json])
            #
            # For now, fake it so your Mac can still show UI:
            output = json.dumps({
                "sum": total_sum,
                "average": avg,
                "min": mn,
                "max": mx
            })

            gpu_end = time.time()
            gpu_ms = (gpu_end - gpu_start) * 1000

        except FileNotFoundError:
            # GPU missing → make front-end happy
            gpu_ms = -1  # -1 means "GPU unavailable"

        return jsonify({
            "count": len(values),
            "sum": total_sum,
            "average": avg,
            "min": mn,
            "max": mx,
            "gpuMilliseconds": gpu_ms,
            "cpuMilliseconds": cpu_ms
        })

    except Exception as e:
        return jsonify({"error": str(e)}), 500


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
