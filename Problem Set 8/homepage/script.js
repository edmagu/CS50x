// Simple interactivity for homepage
document.addEventListener("DOMContentLoaded", function() {
  const greetButton = document.getElementById("greetButton");
  if (greetButton) {
    greetButton.addEventListener("click", function() {
      alert("Hello there! Thanks for visiting my homepage 😄");
    });
  }

  const contactForm = document.getElementById("contactForm");
  if (contactForm) {
    contactForm.addEventListener("submit", function(e) {
      e.preventDefault();
      document.getElementById("formStatus").textContent = "Message sent successfully!";
    });
  }
});
