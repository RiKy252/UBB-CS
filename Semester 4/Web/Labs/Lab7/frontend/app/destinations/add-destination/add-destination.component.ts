import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { HttpClient } from '@angular/common/http';
import { RouterModule } from '@angular/router';

@Component({
  selector: 'app-add-destination',
  standalone: true,
  imports: [CommonModule, FormsModule, RouterModule],
  templateUrl: './add-destination.component.html',
  styleUrls: ['./add-destination.component.css']
})
export class AddDestinationComponent {
  location = '';
  country = '';
  description = '';
  tourist_targets = '';
  cost_per_day: number | null = null;

  constructor(private http: HttpClient, public router: Router) {}

  addDestination() {
    const payload = {
      location: this.location,
      country: this.country,
      description: this.description,
      tourist_targets: this.tourist_targets,
      cost_per_day: this.cost_per_day
    };

    this.http.post('http://localhost/vacation_app/add_destination.php', payload)
      .subscribe({
        next: () => this.router.navigate(['/']),
        error: (err) => alert('Failed to add destination: ' + err.message)
      });
  }
}
